<template>
  <section class="summary-cards">
    <StatCard label="Balance total" :value="formatCurrency(metrics.balanceTotal)" tone="balance" />
    <StatCard label="Ingresos del mes" :value="formatCurrency(metrics.monthlyIncome)" tone="income" />
    <StatCard label="Gastos del mes" :value="formatCurrency(metrics.monthlyExpenses)" tone="expense" />
    <StatCard label="Ahorro estimado" :value="formatCurrency(metrics.monthlySavings)" tone="savings" />
    <StatCard label="Deuda total" :value="formatCurrency(metrics.debtTotal)" tone="debt" />
    <StatCard label="Tasa de ahorro" :value="`${metrics.savingsRate.toFixed(1)}%`" tone="neutral" />
  </section>
</template>

<script setup lang="ts">
import StatCard from '@/components/ui/StatCard.vue'
import { useFinanceStore } from '@/stores/financeStore'

const { metrics } = useFinanceStore()

function formatCurrency(value: number): string {
  return new Intl.NumberFormat('es-SV', {
    style: 'currency',
    currency: 'USD',
  }).format(value)
}
</script>

<style scoped lang="scss">
.summary-cards {
  display: grid;
  grid-template-columns: repeat(6, minmax(0, 1fr));
  gap: 0.85rem;
}

@media (max-width: 1280px) {
  .summary-cards {
    grid-template-columns: repeat(3, minmax(0, 1fr));
  }
}

@media (max-width: 720px) {
  .summary-cards {
    grid-template-columns: 1fr;
  }
}
</style>
