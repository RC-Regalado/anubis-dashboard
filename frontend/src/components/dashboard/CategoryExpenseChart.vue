<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Gastos por categoria</h2>
    </header>
    <div class="bar-list">
      <article v-for="item in categoryExpenses" :key="item.name" class="bar-row">
        <div class="bar-row__meta">
          <strong>{{ item.name }}</strong>
          <span>{{ formatCurrency(item.amount) }}</span>
        </div>
        <div class="bar-row__track">
          <span class="bar-row__fill" :style="{ width: `${widthFor(item.amount)}%` }"></span>
        </div>
      </article>
      <p v-if="!categoryExpenses.length" class="empty">Sin gastos este mes.</p>
    </div>
  </section>
</template>

<script setup lang="ts">
import { computed } from 'vue'
import { useFinanceStore } from '@/stores/financeStore'

const { categoryExpenses } = useFinanceStore()
const maxAmount = computed(() => Math.max(...categoryExpenses.value.map((item) => item.amount), 1))

function widthFor(amount: number): number {
  return Math.max(6, Math.round((amount / maxAmount.value) * 100))
}

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

.bar-list {
  display: grid;
  gap: 0.85rem;
}

.bar-row__meta {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
  margin-bottom: 0.35rem;
}

.bar-row__meta span {
  color: #607089;
}

.bar-row__track {
  height: 0.65rem;
  border-radius: 999px;
  background: #edf1f6;
  overflow: hidden;
}

.bar-row__fill {
  display: block;
  height: 100%;
  border-radius: inherit;
  background: #c2413d;
}

.empty {
  margin: 0;
  color: #607089;
}
</style>
