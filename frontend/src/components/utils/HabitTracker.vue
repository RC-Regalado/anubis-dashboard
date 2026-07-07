<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Habitos</h2>
    </header>
    <div class="habit-list">
      <button
        v-for="habit in state.habits"
        :key="habit.id"
        class="habit-row"
        :class="{ 'habit-row--done': habit.completedToday }"
        type="button"
        @click="toggleHabit(habit.id)"
      >
        <span class="habit-row__check">{{ habit.completedToday ? '✓' : '' }}</span>
        <span>
          <strong>{{ habit.name }}</strong>
          <small>{{ habit.target }} · racha {{ habit.streak }}</small>
        </span>
      </button>
    </div>
  </section>
</template>

<script setup lang="ts">
import { useUtilsStore } from '@/stores/utilsStore'

const { state, toggleHabit } = useUtilsStore()
</script>

<style scoped lang="scss">
.panel {
  padding: 1rem;
  border: 1px solid #d8dee8;
  border-radius: 8px;
  background: #ffffff;
}

.panel__header h2 {
  margin: 0 0 1rem;
  font-size: 1rem;
}

.habit-list {
  display: grid;
  gap: 0.65rem;
}

.habit-row {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  width: 100%;
  padding: 0.75rem;
  border: 1px solid #d8dee8;
  border-radius: 8px;
  background: #ffffff;
  text-align: left;
}

.habit-row--done {
  border-color: #168a52;
  background: #eef8f2;
}

.habit-row__check {
  display: grid;
  place-items: center;
  width: 1.5rem;
  height: 1.5rem;
  border: 1px solid #a8b3c4;
  border-radius: 50%;
  color: #168a52;
  font-weight: 800;
}

.habit-row span:last-child {
  display: grid;
  gap: 0.15rem;
}

small {
  color: #607089;
}
</style>
