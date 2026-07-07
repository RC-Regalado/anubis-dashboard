<template>
  <form class="finance-form" @submit.prevent="submit">
    <label class="field">
      <span>Nombre</span>
      <input v-model="draft.name" class="form-control" required />
    </label>

    <BaseSelect v-model="draft.type" label="Tipo" :options="typeOptions" />

    <label class="field">
      <span>Moneda</span>
      <input v-model="draft.currency" class="form-control" maxlength="3" required />
    </label>

    <label class="field">
      <span>Balance</span>
      <input v-model.number="draft.balance" class="form-control" type="number" step="0.01" required />
    </label>

    <footer class="finance-form__actions">
      <button class="btn btn-primary" type="submit">Guardar cuenta</button>
    </footer>
  </form>
</template>

<script setup lang="ts">
import { reactive } from 'vue'
import BaseSelect from '@/components/ui/BaseSelect.vue'
import { useFinanceStore } from '@/stores/financeStore'
import type { AccountType } from '@/stores/financeStore'

const emit = defineEmits<{ saved: [] }>()
const store = useFinanceStore()

const draft = reactive({
  name: '',
  type: 'bank' as AccountType,
  currency: 'USD',
  balance: 0,
})

const typeOptions: Array<{ label: string; value: AccountType }> = [
  { label: 'Efectivo', value: 'cash' },
  { label: 'Banco', value: 'bank' },
  { label: 'Ahorro', value: 'savings' },
  { label: 'Inversion', value: 'investment' },
  { label: 'Tarjeta', value: 'credit_card' },
  { label: 'Prestamo', value: 'loan' },
]

function submit() {
  store.addAccount({ ...draft })
  draft.name = ''
  draft.balance = 0
  emit('saved')
}
</script>

<style scoped lang="scss">
.finance-form {
  display: grid;
  grid-template-columns: repeat(2, minmax(0, 1fr));
  gap: 1rem;
}

.field {
  display: grid;
  gap: 0.35rem;
}

.field span {
  color: #334155;
  font-weight: 700;
}

.finance-form__actions {
  grid-column: 1 / -1;
  display: flex;
  justify-content: flex-end;
}

@media (max-width: 720px) {
  .finance-form {
    grid-template-columns: 1fr;
  }
}
</style>
