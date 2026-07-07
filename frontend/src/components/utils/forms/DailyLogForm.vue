<template>
  <form class="utils-form" @submit.prevent="submit">
    <label class="field">
      <span>Fecha</span>
      <input v-model="draft.date" class="form-control" type="date" required />
    </label>
    <label class="field">
      <span>Peso</span>
      <input v-model.number="draft.weight" class="form-control" type="number" step="0.1" />
    </label>
    <label class="field">
      <span>Cintura</span>
      <input v-model.number="draft.waist" class="form-control" type="number" step="0.1" />
    </label>
    <label class="field">
      <span>Pecho</span>
      <input v-model.number="draft.chest" class="form-control" type="number" step="0.1" />
    </label>
    <label class="field">
      <span>Muslo</span>
      <input v-model.number="draft.thigh" class="form-control" type="number" step="0.1" />
    </label>
    <label class="field">
      <span>Sueno horas</span>
      <input v-model.number="draft.sleepHours" class="form-control" type="number" step="0.1" />
    </label>
    <label class="field">
      <span>Calidad sueno 1-5</span>
      <input v-model.number="draft.sleepQuality" class="form-control" type="number" min="1" max="5" />
    </label>
    <label class="field">
      <span>Hora dormir</span>
      <input v-model="draft.bedtime" class="form-control" type="time" />
    </label>
    <label class="field">
      <span>Hora despertar</span>
      <input v-model="draft.wakeTime" class="form-control" type="time" />
    </label>
    <label class="field">
      <span>Despertares</span>
      <input v-model.number="draft.nightlyWakeups" class="form-control" type="number" min="0" />
    </label>
    <label class="field">
      <span>Energía 1-5</span>
      <input v-model.number="draft.energy" class="form-control" type="number" min="1" max="5" />
    </label>
    <label class="field">
      <span>Estrés 1-5</span>
      <input v-model.number="draft.stress" class="form-control" type="number" min="1" max="5" />
    </label>
    <label class="field">
      <span>DOMS 1-5</span>
      <input v-model.number="draft.doms" class="form-control" type="number" min="1" max="5" />
    </label>
    <label class="field">
      <span>Dolor general</span>
      <input v-model.number="draft.generalPain" class="form-control" type="number" min="1" max="5" />
    </label>
    <label class="field">
      <span>Dolor específico</span>
      <input v-model="draft.specificPain" class="form-control" placeholder="piriforme, hombro..." />
    </label>
    <label class="field">
      <span>Motivación 1-5</span>
      <input v-model.number="draft.motivation" class="form-control" type="number" min="1" max="5" />
    </label>
    <label class="field">
      <span>Agua L</span>
      <input v-model.number="draft.waterLiters" class="form-control" type="number" step="0.1" />
    </label>
    <label class="field">
      <span>Calorías</span>
      <input v-model.number="draft.calories" class="form-control" type="number" />
    </label>
    <label class="field">
      <span>Proteína g</span>
      <input v-model.number="draft.protein" class="form-control" type="number" />
    </label>
    <label class="field">
      <span>Azúcar simple g</span>
      <input v-model.number="draft.simpleSugar" class="form-control" type="number" />
    </label>
    <label class="field">
      <span>Ayuno h</span>
      <input v-model.number="draft.fastingHours" class="form-control" type="number" step="0.5" />
    </label>
    <label class="field">
      <span>Pasos</span>
      <input v-model.number="draft.steps" class="form-control" type="number" />
    </label>
    <label class="field">
      <span>Distancia km</span>
      <input v-model.number="draft.distanceKm" class="form-control" type="number" step="0.1" />
    </label>
    <label class="field">
      <span>Activo min</span>
      <input v-model.number="draft.activeMinutes" class="form-control" type="number" />
    </label>
    <label class="field">
      <span>RHR</span>
      <input v-model.number="draft.restingHeartRate" class="form-control" type="number" />
    </label>
    <label class="field">
      <span>FCR</span>
      <input v-model.number="draft.recoveryHeartRate" class="form-control" type="number" />
    </label>
    <label class="field">
      <span>Presión sistólica</span>
      <input v-model.number="draft.bloodPressureSystolic" class="form-control" type="number" />
    </label>
    <label class="field">
      <span>Presión diastólica</span>
      <input v-model.number="draft.bloodPressureDiastolic" class="form-control" type="number" />
    </label>
    <label class="field field--full">
      <span>Nota</span>
      <textarea v-model="draft.note" class="form-control" rows="3"></textarea>
    </label>
    <footer class="utils-form__actions">
      <button class="btn btn-primary" type="submit">Guardar día</button>
    </footer>
  </form>
</template>

<script setup lang="ts">
import { reactive } from 'vue'
import { useUtilsStore } from '@/stores/utilsStore'
import type { DayInput } from '@/stores/utilsStore'

const emit = defineEmits<{ saved: [] }>()
const { addDay, latestDay } = useUtilsStore()

const today = new Date().toISOString().slice(0, 10)
const base = latestDay.value

const draft = reactive<DayInput>({
  date: today,
  weight: base?.weight ?? 0,
  waist: base?.waist ?? 0,
  chest: base?.chest ?? 0,
  thigh: base?.thigh ?? 0,
  sleepHours: 0,
  sleepQuality: 3,
  bedtime: '23:00',
  wakeTime: '06:00',
  nightlyWakeups: 0,
  wakeEnergy: 3,
  energy: 3,
  stress: 3,
  doms: 3,
  generalPain: 1,
  specificPain: '',
  motivation: 3,
  waterLiters: 0,
  calories: 0,
  protein: 0,
  simpleSugar: 0,
  fastingHours: 0,
  steps: 0,
  distanceKm: 0,
  activeMinutes: 0,
  restingHeartRate: 0,
  recoveryHeartRate: 0,
  bloodPressureSystolic: 0,
  bloodPressureDiastolic: 0,
  note: '',
})

function submit() {
  addDay({ ...draft })
  emit('saved')
}
</script>

<style scoped lang="scss">
.utils-form {
  display: grid;
  grid-template-columns: repeat(3, minmax(0, 1fr));
  gap: 0.85rem;
}

.field {
  display: grid;
  gap: 0.3rem;
}

.field span {
  color: #334155;
  font-weight: 700;
}

.field--full,
.utils-form__actions {
  grid-column: 1 / -1;
}

.utils-form__actions {
  display: flex;
  justify-content: flex-end;
}

@media (max-width: 900px) {
  .utils-form {
    grid-template-columns: 1fr;
  }
}
</style>
