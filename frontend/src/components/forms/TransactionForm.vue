<template>
  <form class="finance-form" @submit.prevent="submit">
    <BaseSelect v-model="draft.type" label="Tipo" :options="typeOptions" />

    <label class="field">
      <span>Monto</span>
      <input v-model.number="draft.amount" class="form-control" type="number" min="0" step="0.01" required />
    </label>

    <label class="field">
      <span>Fecha</span>
      <input v-model="draft.date" class="form-control" type="date" required />
    </label>

    <BaseSelect
      v-model="draft.accountFromId"
      label="Cuenta origen"
      placeholder="Seleccionar"
      :options="accountOptions"
    />

    <BaseSelect
      v-model="draft.accountToId"
      label="Cuenta destino"
      placeholder="Seleccionar"
      :options="accountOptions"
    />

    <BaseSelect
      v-model="draft.creditCardId"
      label="Tarjeta asociada"
      placeholder="Sin tarjeta"
      :options="creditCardOptions"
    />

    <BaseSelect
      v-model="draft.categoryId"
      label="Categoria"
      placeholder="Sin categoria"
      :options="categoryOptions"
    />

    <BaseSelect
      v-model="draft.merchantId"
      label="Comercio"
      placeholder="Sin comercio"
      :options="merchantOptions"
    />

    <label class="field">
      <span>Etiquetas</span>
      <input v-model="tagsInput" class="form-control" placeholder="hogar, recurrente, banco" />
    </label>

    <BaseSelect v-model="draft.status" label="Estado" :options="statusOptions" />

    <label class="field field--full">
      <span>Nota</span>
      <textarea v-model="draft.notes" class="form-control" rows="3"></textarea>
    </label>

    <footer class="finance-form__actions">
      <button class="btn btn-primary" type="submit">Guardar transaccion</button>
    </footer>
  </form>
</template>

<script setup lang="ts">
import { computed, reactive, ref } from 'vue'
import BaseSelect from '@/components/ui/BaseSelect.vue'
import { useFinanceStore } from '@/stores/financeStore'
import type { TransactionInput, TransactionStatus, TransactionType } from '@/stores/financeStore'

const emit = defineEmits<{
  saved: []
}>()

const store = useFinanceStore()
const tagsInput = ref('')
const draft = reactive<TransactionInput>({
  type: 'expense',
  amount: 0,
  date: new Date().toISOString().slice(0, 10),
  accountFromId: 'acc-checking',
  accountToId: '',
  creditCardId: '',
  categoryId: 'cat-food',
  merchantId: '',
  tags: [],
  notes: '',
  status: 'cleared',
})

const typeOptions: Array<{ label: string; value: TransactionType }> = [
  { label: 'Ingreso', value: 'income' },
  { label: 'Gasto', value: 'expense' },
  { label: 'Transferencia', value: 'transfer' },
  { label: 'Pago de tarjeta', value: 'card_payment' },
  { label: 'Comision', value: 'fee' },
]

const statusOptions: Array<{ label: string; value: TransactionStatus }> = [
  { label: 'Pendiente', value: 'pending' },
  { label: 'Liquidado', value: 'cleared' },
  { label: 'Conciliado', value: 'reconciled' },
]

const accountOptions = computed(() =>
  store.state.accounts.map((account) => ({ label: account.name, value: account.id })),
)
const creditCardOptions = computed(() =>
  store.state.creditCards.map((card) => ({ label: card.name, value: card.id })),
)
const categoryOptions = computed(() =>
  store.state.categories.map((category) => ({ label: category.name, value: category.id })),
)
const merchantOptions = computed(() =>
  store.state.merchants.map((merchant) => ({ label: merchant.name, value: merchant.id })),
)

function submit() {
  store.addTransaction({
    ...draft,
    tags: tagsInput.value
      .split(',')
      .map((tag) => tag.trim())
      .filter(Boolean),
  })

  draft.amount = 0
  draft.notes = ''
  tagsInput.value = ''
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

.field--full,
.finance-form__actions {
  grid-column: 1 / -1;
}

.finance-form__actions {
  display: flex;
  justify-content: flex-end;
}

@media (max-width: 720px) {
  .finance-form {
    grid-template-columns: 1fr;
  }
}
</style>
