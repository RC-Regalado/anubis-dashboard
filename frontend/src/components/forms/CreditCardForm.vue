<template>
  <form class="finance-form" @submit.prevent="submit">
    <label class="field">
      <span>Nombre</span>
      <input v-model="draft.name" class="form-control" required />
    </label>

    <label class="field">
      <span>Limite</span>
      <input v-model.number="draft.limit" class="form-control" min="0" type="number" step="0.01" required />
    </label>

    <label class="field">
      <span>Saldo actual</span>
      <input v-model.number="draft.currentBalance" class="form-control" min="0" type="number" step="0.01" required />
    </label>

    <label class="field">
      <span>Corte</span>
      <input v-model="draft.closingDate" class="form-control" type="date" required />
    </label>

    <label class="field">
      <span>Vencimiento</span>
      <input v-model="draft.dueDate" class="form-control" type="date" required />
    </label>

    <BaseSelect v-model="draft.accountId" label="Cuenta de pago" :options="accountOptions" />

    <footer class="finance-form__actions">
      <button class="btn btn-primary" type="submit">Guardar tarjeta</button>
    </footer>
  </form>
</template>

<script setup lang="ts">
import { computed, reactive } from 'vue'
import BaseSelect from '@/components/ui/BaseSelect.vue'
import { useFinanceStore } from '@/stores/financeStore'

const emit = defineEmits<{ saved: [] }>()
const store = useFinanceStore()

const draft = reactive({
  name: '',
  limit: 0,
  currentBalance: 0,
  closingDate: new Date().toISOString().slice(0, 10),
  dueDate: new Date().toISOString().slice(0, 10),
  accountId: 'acc-checking',
})

const accountOptions = computed(() =>
  store.state.accounts.map((account) => ({ label: account.name, value: account.id })),
)

function submit() {
  store.addCreditCard({ ...draft })
  draft.name = ''
  draft.limit = 0
  draft.currentBalance = 0
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
