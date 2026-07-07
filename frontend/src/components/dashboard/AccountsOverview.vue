<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Cuentas</h2>
    </header>
    <div class="account-list">
      <article v-for="account in state.accounts" :key="account.id" class="account-row">
        <div>
          <strong>{{ account.name }}</strong>
          <span>{{ typeLabel(account.type) }}</span>
        </div>
        <strong :class="{ negative: account.balance < 0 }">{{ formatCurrency(account.balance) }}</strong>
      </article>
    </div>
  </section>
</template>

<script setup lang="ts">
import { useFinanceStore } from '@/stores/financeStore'
import type { AccountType } from '@/stores/financeStore'

const { state } = useFinanceStore()

function typeLabel(type: AccountType): string {
  const labels: Record<AccountType, string> = {
    cash: 'Efectivo',
    bank: 'Banco',
    savings: 'Ahorro',
    investment: 'Inversion',
    credit_card: 'Tarjeta',
    loan: 'Prestamo',
  }

  return labels[type]
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

.account-list {
  display: grid;
  gap: 0.75rem;
}

.account-row {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
  padding-bottom: 0.75rem;
  border-bottom: 1px solid #e7ebf1;
}

.account-row:last-child {
  padding-bottom: 0;
  border-bottom: 0;
}

.account-row div {
  display: grid;
  gap: 0.15rem;
}

.account-row span {
  color: #607089;
  font-size: 0.88rem;
}

.negative {
  color: #c2413d;
}
</style>
