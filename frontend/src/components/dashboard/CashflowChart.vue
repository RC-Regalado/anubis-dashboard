<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Flujo mensual</h2>
      <span>Ingresos vs gastos</span>
    </header>
    <div class="cashflow">
      <article v-for="item in monthlyCashflow" :key="item.date" class="cashflow__day">
        <div class="cashflow__bars">
          <span
            class="cashflow__bar cashflow__bar--income"
            :style="{ height: `${heightFor(item.income)}%` }"
          ></span>
          <span
            class="cashflow__bar cashflow__bar--expense"
            :style="{ height: `${heightFor(item.expenses)}%` }"
          ></span>
        </div>
        <small>{{ item.date.slice(8) }}</small>
      </article>
      <p v-if="!monthlyCashflow.length" class="empty">Sin movimientos en el mes.</p>
    </div>
    <footer class="legend">
      <span><i class="income"></i>Ingresos</span>
      <span><i class="expense"></i>Gastos</span>
    </footer>
  </section>
</template>

<script setup lang="ts">
import { computed } from 'vue'
import { useFinanceStore } from '@/stores/financeStore'

const { monthlyCashflow } = useFinanceStore()
const maxAmount = computed(() =>
  Math.max(...monthlyCashflow.value.flatMap((item) => [item.income, item.expenses]), 1),
)

function heightFor(amount: number): number {
  return Math.max(amount > 0 ? 8 : 0, Math.round((amount / maxAmount.value) * 100))
}
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
.legend {
  color: #607089;
  font-size: 0.9rem;
}

.cashflow {
  min-height: 190px;
  display: grid;
  grid-auto-flow: column;
  grid-auto-columns: minmax(34px, 1fr);
  gap: 0.65rem;
  align-items: end;
  overflow-x: auto;
}

.cashflow__day {
  display: grid;
  gap: 0.45rem;
  justify-items: center;
}

.cashflow__bars {
  height: 150px;
  display: flex;
  align-items: end;
  gap: 0.25rem;
}

.cashflow__bar {
  width: 0.75rem;
  min-height: 0;
  border-radius: 999px 999px 0 0;
}

.cashflow__bar--income {
  background: #168a52;
}

.cashflow__bar--expense {
  background: #c2413d;
}

.legend {
  display: flex;
  gap: 1rem;
  margin-top: 0.85rem;
}

.legend i {
  display: inline-block;
  width: 0.65rem;
  height: 0.65rem;
  margin-right: 0.35rem;
  border-radius: 50%;
}

.income {
  background: #168a52;
}

.expense {
  background: #c2413d;
}

.empty {
  margin: 0;
  color: #607089;
}
</style>
