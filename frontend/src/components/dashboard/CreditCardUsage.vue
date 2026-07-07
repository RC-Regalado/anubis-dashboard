<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Uso de tarjetas</h2>
    </header>
    <div class="card-list">
      <article v-for="card in creditCardUsage" :key="card.id" class="credit-card">
        <div class="credit-card__top">
          <strong>{{ card.name }}</strong>
          <span>{{ Math.round(card.usageRate) }}%</span>
        </div>
        <div class="credit-card__track">
          <span class="credit-card__fill" :style="{ width: `${Math.min(card.usageRate, 100)}%` }"></span>
        </div>
        <div class="credit-card__meta">
          <span>{{ formatCurrency(card.currentBalance) }}</span>
          <span>{{ formatCurrency(card.limit) }}</span>
        </div>
      </article>
    </div>
  </section>
</template>

<script setup lang="ts">
import { useFinanceStore } from '@/stores/financeStore'

const { creditCardUsage } = useFinanceStore()

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

.card-list {
  display: grid;
  gap: 1rem;
}

.credit-card__top,
.credit-card__meta {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
}

.credit-card__track {
  height: 0.7rem;
  margin: 0.45rem 0;
  border-radius: 999px;
  background: #edf1f6;
  overflow: hidden;
}

.credit-card__fill {
  display: block;
  height: 100%;
  border-radius: inherit;
  background: #315fbc;
}

.credit-card__meta {
  color: #607089;
  font-size: 0.9rem;
}
</style>
