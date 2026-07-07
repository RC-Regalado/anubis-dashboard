<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Transacciones recientes</h2>
    </header>
    <BaseTable :columns="columns" :rows="rows">
      <template #amount="{ row }">
        <strong :class="amountClass(row.type as string)">
          {{ formatCurrency(Number(row.amount)) }}
        </strong>
      </template>
      <template #type="{ row }">
        <span class="type-chip">{{ typeLabel(row.type as string) }}</span>
      </template>
      <template #merchantName="{ row }">
        {{ row.merchantName || row.creditCardName || row.accountToName || '-' }}
      </template>
    </BaseTable>
  </section>
</template>

<script setup lang="ts">
import { computed } from 'vue'
import BaseTable from '@/components/ui/BaseTable.vue'
import { useFinanceStore } from '@/stores/financeStore'

const { recentTransactions } = useFinanceStore()

const columns = [
  { key: 'date', label: 'Fecha' },
  { key: 'type', label: 'Tipo' },
  { key: 'merchantName', label: 'Comercio' },
  { key: 'categoryName', label: 'Categoria' },
  { key: 'amount', label: 'Monto' },
  { key: 'status', label: 'Estado' },
]

const rows = computed(() =>
  recentTransactions.value.map((transaction) => ({
    ...transaction,
  })),
)

function typeLabel(type: string): string {
  const labels: Record<string, string> = {
    income: 'Ingreso',
    expense: 'Gasto',
    transfer: 'Transferencia',
    card_payment: 'Pago tarjeta',
    fee: 'Comision',
  }

  return labels[type] ?? type
}

function amountClass(type: string): string {
  if (type === 'income') return 'amount amount--income'
  if (type === 'transfer' || type === 'card_payment') return 'amount amount--neutral'
  return 'amount amount--expense'
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

.type-chip {
  display: inline-flex;
  padding: 0.2rem 0.5rem;
  border-radius: 999px;
  background: #eef2f7;
  color: #334155;
  font-size: 0.82rem;
  font-weight: 700;
}

.amount--income {
  color: #168a52;
}

.amount--expense {
  color: #c2413d;
}

.amount--neutral {
  color: #315fbc;
}
</style>
