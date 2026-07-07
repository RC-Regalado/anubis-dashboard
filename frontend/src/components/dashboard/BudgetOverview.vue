<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Presupuestos</h2>
    </header>
    <div class="budget-list">
      <article v-for="budget in budgetUsage" :key="budget.id" class="budget">
        <div class="budget__top">
          <strong>{{ budget.categoryName }}</strong>
          <span>{{ Math.round(budget.usageRate) }}%</span>
        </div>
        <div class="budget__track">
          <span
            class="budget__fill"
            :class="{ 'budget__fill--over': budget.usageRate > 100 }"
            :style="{ width: `${Math.min(budget.usageRate, 100)}%` }"
          ></span>
        </div>
        <div class="budget__meta">
          <span>{{ formatCurrency(budget.spent) }}</span>
          <span>{{ formatCurrency(budget.limitAmount) }}</span>
        </div>
      </article>
    </div>
  </section>
</template>

<script setup lang="ts">
import { useFinanceStore } from '@/stores/financeStore'

const { budgetUsage } = useFinanceStore()

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

.budget-list {
  display: grid;
  gap: 1rem;
}

.budget__top,
.budget__meta {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
}

.budget__track {
  height: 0.7rem;
  margin: 0.45rem 0;
  border-radius: 999px;
  background: #edf1f6;
  overflow: hidden;
}

.budget__fill {
  display: block;
  height: 100%;
  border-radius: inherit;
  background: #315fbc;
}

.budget__fill--over {
  background: #c2413d;
}

.budget__meta {
  color: #607089;
  font-size: 0.9rem;
}
</style>
