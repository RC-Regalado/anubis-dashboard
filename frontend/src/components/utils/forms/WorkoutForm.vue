<template>
  <form class="utils-form" @submit.prevent="submit">
    <label class="field">
      <span>Fecha</span>
      <input v-model="workout.date" class="form-control" type="date" required />
    </label>
    <BaseSelect v-model="workout.type" label="Tipo" :options="typeOptions" />
    <label class="field">
      <span>Duración min</span>
      <input v-model.number="workout.durationMinutes" class="form-control" type="number" min="0" />
    </label>
    <label class="field">
      <span>RPE 1-13</span>
      <input v-model.number="workout.intensityRpe" class="form-control" type="number" min="1" max="13" />
    </label>
    <label class="field">
      <span>FC promedio</span>
      <input v-model.number="workout.averageHeartRate" class="form-control" type="number" />
    </label>
    <label class="field">
      <span>FC máxima</span>
      <input v-model.number="workout.maxHeartRate" class="form-control" type="number" />
    </label>
    <label class="field">
      <span>Descanso real min</span>
      <input v-model.number="workout.restMinutes" class="form-control" type="number" min="0" />
    </label>

    <section class="exercise-block field--full">
      <header>
        <strong>Ejercicios</strong>
        <button class="btn btn-sm btn-outline-secondary" type="button" @click="addExerciseRow">
          Agregar
        </button>
      </header>
      <div v-for="(exercise, index) in exercises" :key="index" class="exercise-row">
        <input v-model="exercise.exercise" class="form-control" placeholder="Ejercicio" />
        <input v-model.number="exercise.weight" class="form-control" type="number" step="0.5" placeholder="Peso" />
        <input v-model.number="exercise.reps" class="form-control" type="number" placeholder="Reps" />
        <input v-model.number="exercise.sets" class="form-control" type="number" placeholder="Series" />
      </div>
    </section>

    <footer class="utils-form__actions">
      <button class="btn btn-primary" type="submit">Guardar entrenamiento</button>
    </footer>
  </form>
</template>

<script setup lang="ts">
import { reactive } from 'vue'
import BaseSelect from '@/components/ui/BaseSelect.vue'
import { useUtilsStore } from '@/stores/utilsStore'
import type { WorkoutInput, WorkoutType } from '@/stores/utilsStore'

const emit = defineEmits<{ saved: [] }>()
const { addWorkout } = useUtilsStore()

const workout = reactive<WorkoutInput>({
  date: new Date().toISOString().slice(0, 10),
  type: 'strength',
  durationMinutes: 60,
  intensityRpe: 8,
  averageHeartRate: 0,
  maxHeartRate: 0,
  restMinutes: 0,
})

const exercises = reactive([
  { exercise: '', weight: 0, reps: 0, sets: 0 },
])

const typeOptions: Array<{ label: string; value: WorkoutType }> = [
  { label: 'Fuerza', value: 'strength' },
  { label: 'Cardio', value: 'cardio' },
]

function addExerciseRow() {
  exercises.push({ exercise: '', weight: 0, reps: 0, sets: 0 })
}

function submit() {
  addWorkout({ ...workout }, exercises.map((exercise) => ({ ...exercise })))
  exercises.splice(0, exercises.length, { exercise: '', weight: 0, reps: 0, sets: 0 })
  emit('saved')
}
</script>

<style scoped lang="scss">
.utils-form {
  display: grid;
  grid-template-columns: repeat(2, minmax(0, 1fr));
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

.exercise-block {
  display: grid;
  gap: 0.75rem;
}

.exercise-block header {
  display: flex;
  align-items: center;
  justify-content: space-between;
}

.exercise-row {
  display: grid;
  grid-template-columns: minmax(160px, 1fr) repeat(3, minmax(80px, 0.45fr));
  gap: 0.5rem;
}

.utils-form__actions {
  display: flex;
  justify-content: flex-end;
}

@media (max-width: 900px) {
  .utils-form,
  .exercise-row {
    grid-template-columns: 1fr;
  }
}
</style>
