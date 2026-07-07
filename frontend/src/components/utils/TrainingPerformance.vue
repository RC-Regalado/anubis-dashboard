<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Rendimiento en entrenamiento</h2>
      <span>{{ state.workouts.length }} sesiones</span>
    </header>
    <div class="training-list">
      <article v-for="exercise in workoutVolumeByExercise.slice(0, 6)" :key="exercise.id" class="training-row">
        <div>
          <strong>{{ exercise.exercise }}</strong>
          <span>{{ exercise.sets }} series x {{ exercise.reps }} reps</span>
        </div>
        <strong>{{ Math.round(exercise.volume) }} kg</strong>
      </article>
    </div>
  </section>
</template>

<script setup lang="ts">
import { useUtilsStore } from '@/stores/utilsStore'

const { state, workoutVolumeByExercise } = useUtilsStore()
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
.training-row span {
  color: #607089;
}

.training-list {
  display: grid;
  gap: 0.75rem;
}

.training-row {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
  padding-bottom: 0.75rem;
  border-bottom: 1px solid #e7ebf1;
}

.training-row:last-child {
  padding-bottom: 0;
  border-bottom: 0;
}

.training-row div {
  display: grid;
  gap: 0.2rem;
}
</style>
