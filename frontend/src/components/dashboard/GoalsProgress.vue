<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Metas financieras</h2>
    </header>
    <div class="goal-list">
      <article v-for="goal in goalsProgress" :key="goal.id" class="goal">
        <div class="goal__top">
          <strong>{{ goal.name }}</strong>
          <span>{{ Math.round(goal.progressRate) }}%</span>
        </div>
        <div class="goal__track">
          <span class="goal__fill" :style="{ width: `${Math.min(goal.progressRate, 100)}%` }"></span>
        </div>
        <div class="goal__meta">
          <span>{{ formatCurrency(goal.currentAmount) }} de {{ formatCurrency(goal.targetAmount) }}</span>
          <span>{{ goal.dueDate }}</span>
        </div>
      </article>
    </div>
  </section>
</template>

<script setup lang="ts">
import { useFinanceStore } from '@/stores/financeStore'

const { goalsProgress } = useFinanceStore()

function formatCurrency(value: number): string {
  return new Intl.NumberFormat('es-SV', { style: 'currency', currency: 'USD' }).format(value)
}
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

.goal-list {
  display: grid;
  gap: 1rem;
}

.goal__top,
.goal__meta {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
}

.goal__track {
  height: 0.7rem;
  margin: 0.45rem 0;
  border-radius: 999px;
  background: #edf1f6;
  overflow: hidden;
}

.goal__fill {
  display: block;
  height: 100%;
  border-radius: inherit;
  background: #1f7a8c;
}

.goal__meta {
  color: #607089;
  font-size: 0.9rem;
}
</style>
