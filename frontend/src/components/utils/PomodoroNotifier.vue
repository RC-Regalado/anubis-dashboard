<template>
  <section class="panel">
    <header class="panel__header">
      <div>
        <h2>Pomodoro</h2>
        <span>{{ currentCycleLabel }}</span>
      </div>
      <strong class="status" :class="`status--${permissionState}`">{{ permissionLabel }}</strong>
    </header>

    <div class="timer-display">{{ formattedRemaining }}</div>

    <div class="config-grid">
      <label class="field">
        <span>Enfoque</span>
        <input v-model.number="config.focusMinutes" class="form-control" min="1" max="180" type="number" />
      </label>
      <label class="field">
        <span>Descanso</span>
        <input v-model.number="config.shortBreakMinutes" class="form-control" min="1" max="60" type="number" />
      </label>
      <label class="field">
        <span>Descanso largo</span>
        <input v-model.number="config.longBreakMinutes" class="form-control" min="1" max="90" type="number" />
      </label>
      <label class="field">
        <span>Ciclos</span>
        <input v-model.number="config.cyclesBeforeLongBreak" class="form-control" min="1" max="12" type="number" />
      </label>
    </div>

    <div class="actions">
      <button class="btn btn-outline-secondary" type="button" @click="requestNotificationPermission">
        Activar notificaciones
      </button>
      <button class="btn btn-primary" type="button" @click="startPomodoro">
        {{ running ? 'Reiniciar' : 'Iniciar' }}
      </button>
      <button class="btn btn-outline-dark" type="button" @click="pausePomodoro">Pausar</button>
      <button class="btn btn-outline-secondary" type="button" @click="resumePomodoro">Continuar</button>
      <button class="btn btn-outline-danger" type="button" @click="resetPomodoro">Reset</button>
    </div>

    <footer class="cycle-footer">
      <span>Ciclo {{ completedFocusCycles + 1 }}</span>
      <span>{{ statusMessage }}</span>
    </footer>
  </section>
</template>

<script setup lang="ts">
import { computed, onBeforeUnmount, reactive, ref } from 'vue'

type CycleType = 'focus' | 'shortBreak' | 'longBreak'
type PermissionState = 'unsupported' | 'default' | 'granted' | 'denied'

const config = reactive({
  focusMinutes: 25,
  shortBreakMinutes: 5,
  longBreakMinutes: 15,
  cyclesBeforeLongBreak: 4,
})

const currentCycle = ref<CycleType>('focus')
const completedFocusCycles = ref(0)
const remainingMs = ref(toMs(config.focusMinutes))
const targetMs = ref(0)
const pausedMs = ref(0)
const running = ref(false)
const intervalId = ref<number | null>(null)
const statusMessage = ref('Listo')
const permissionState = ref<PermissionState>(getPermissionState())

const currentCycleLabel = computed(() => {
  const labels: Record<CycleType, string> = {
    focus: 'Enfoque',
    shortBreak: 'Descanso corto',
    longBreak: 'Descanso largo',
  }

  return labels[currentCycle.value]
})

const permissionLabel = computed(() => {
  const labels: Record<PermissionState, string> = {
    unsupported: 'No soportado',
    default: 'Permiso pendiente',
    granted: 'Notificaciones activas',
    denied: 'Permiso bloqueado',
  }

  return labels[permissionState.value]
})

const formattedRemaining = computed(() => formatDuration(remainingMs.value))

function getPermissionState(): PermissionState {
  if (!('Notification' in window)) {
    return 'unsupported'
  }

  return Notification.permission as PermissionState
}

async function requestNotificationPermission() {
  if (!('Notification' in window)) {
    permissionState.value = 'unsupported'
    statusMessage.value = 'Este navegador no soporta notificaciones.'
    return
  }

  permissionState.value = (await Notification.requestPermission()) as PermissionState
  statusMessage.value =
    permissionState.value === 'granted'
      ? 'Notificaciones listas.'
      : 'Permiso de notificaciones no concedido.'
}

function notifyUser(title: string, body: string) {
  permissionState.value = getPermissionState()

  if (permissionState.value !== 'granted') {
    statusMessage.value = body
    return
  }

  new Notification(title, {
    body,
    tag: 'sync-pomodoro-cycle',
    silent: false,
  })
}

function sanitizeConfig() {
  config.focusMinutes = clampInt(config.focusMinutes, 25, 1, 180)
  config.shortBreakMinutes = clampInt(config.shortBreakMinutes, 5, 1, 60)
  config.longBreakMinutes = clampInt(config.longBreakMinutes, 15, 1, 90)
  config.cyclesBeforeLongBreak = clampInt(config.cyclesBeforeLongBreak, 4, 1, 12)
}

function durationFor(cycle: CycleType): number {
  if (cycle === 'focus') return toMs(config.focusMinutes)
  if (cycle === 'longBreak') return toMs(config.longBreakMinutes)
  return toMs(config.shortBreakMinutes)
}

function startPomodoro() {
  sanitizeConfig()
  clearTimer()
  currentCycle.value = 'focus'
  completedFocusCycles.value = 0
  remainingMs.value = durationFor(currentCycle.value)
  startCurrentCycle()
}

function startCurrentCycle() {
  clearTimer()
  pausedMs.value = 0
  running.value = true
  targetMs.value = Date.now() + remainingMs.value
  intervalId.value = window.setInterval(tick, 250)
  statusMessage.value = `${currentCycleLabel.value} en curso.`
  tick()
}

function pausePomodoro() {
  if (!running.value) return

  pausedMs.value = remainingMs.value
  running.value = false
  clearTimer()
  statusMessage.value = 'Pausado.'
}

function resumePomodoro() {
  if (running.value || pausedMs.value <= 0) return

  remainingMs.value = pausedMs.value
  startCurrentCycle()
}

function resetPomodoro() {
  clearTimer()
  currentCycle.value = 'focus'
  completedFocusCycles.value = 0
  pausedMs.value = 0
  running.value = false
  remainingMs.value = toMs(config.focusMinutes)
  statusMessage.value = 'Listo'
}

function tick() {
  remainingMs.value = Math.max(0, targetMs.value - Date.now())

  if (remainingMs.value > 0) return

  completeCycle()
}

function completeCycle() {
  clearTimer()
  running.value = false

  const completedLabel = currentCycleLabel.value

  if (currentCycle.value === 'focus') {
    completedFocusCycles.value += 1
    const nextBreak =
      completedFocusCycles.value % config.cyclesBeforeLongBreak === 0 ? 'longBreak' : 'shortBreak'
    currentCycle.value = nextBreak
    remainingMs.value = durationFor(nextBreak)
  } else {
    currentCycle.value = 'focus'
    remainingMs.value = durationFor('focus')
  }

  const nextLabel = currentCycleLabel.value
  const message = `${completedLabel} terminado. Sigue: ${nextLabel}.`
  statusMessage.value = message
  notifyUser('Pomodoro', message)
}

function clearTimer() {
  if (intervalId.value === null) return

  window.clearInterval(intervalId.value)
  intervalId.value = null
}

function toMs(minutes: number): number {
  return Math.max(0, minutes * 60 * 1000)
}

function clampInt(value: number, fallback: number, min: number, max: number): number {
  if (!Number.isFinite(value)) return fallback

  return Math.min(max, Math.max(min, Math.floor(value)))
}

function formatDuration(durationMs: number): string {
  const totalSeconds = Math.max(0, Math.ceil(durationMs / 1000))
  const minutes = Math.floor(totalSeconds / 60)
  const seconds = totalSeconds % 60

  return `${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`
}

onBeforeUnmount(clearTimer)
</script>

<style scoped lang="scss">
.panel {
  padding: 1rem;
  border: 1px solid #d8dee8;
  border-radius: 8px;
  background: #ffffff;
}

.panel__header {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
  margin-bottom: 1rem;
}

.panel__header h2 {
  margin: 0;
  font-size: 1rem;
}

.panel__header span,
.cycle-footer {
  color: #607089;
}

.status {
  align-self: start;
  padding: 0.25rem 0.55rem;
  border-radius: 999px;
  background: #eef2f7;
  color: #334155;
  font-size: 0.78rem;
}

.status--granted {
  background: #eef8f2;
  color: #168a52;
}

.status--denied,
.status--unsupported {
  background: #fff1f1;
  color: #c2413d;
}

.timer-display {
  margin-bottom: 1rem;
  padding: 1rem;
  border-radius: 8px;
  background: #17243a;
  color: #ffffff;
  font-size: 2.4rem;
  font-weight: 800;
  line-height: 1;
  text-align: center;
}

.config-grid {
  display: grid;
  grid-template-columns: repeat(2, minmax(0, 1fr));
  gap: 0.75rem;
}

.field {
  display: grid;
  gap: 0.3rem;
}

.field span {
  color: #334155;
  font-weight: 700;
}

.actions {
  display: flex;
  flex-wrap: wrap;
  gap: 0.5rem;
  margin-top: 1rem;
}

.cycle-footer {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
  margin-top: 1rem;
  font-size: 0.9rem;
}

@media (max-width: 720px) {
  .config-grid {
    grid-template-columns: 1fr;
  }

  .cycle-footer,
  .panel__header {
    flex-direction: column;
  }
}
</style>
