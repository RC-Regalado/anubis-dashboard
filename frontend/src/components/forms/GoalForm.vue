<template>
  <form class="finance-form" @submit.prevent="submit">
    <label class="field">
      <span>Nombre</span>
      <input v-model="draft.name" class="form-control" required />
    </label>

    <label class="field">
      <span>Monto objetivo</span>
      <input v-model.number="draft.targetAmount" class="form-control" type="number" min="0" step="0.01" required />
    </label>

    <label class="field">
      <span>Monto actual</span>
      <input v-model.number="draft.currentAmount" class="form-control" type="number" min="0" step="0.01" required />
    </label>

    <label class="field">
      <span>Fecha limite</span>
      <input v-model="draft.dueDate" class="form-control" type="date" required />
    </label>

    <footer class="finance-form__actions">
      <button class="btn btn-primary" type="submit">Guardar meta</button>
    </footer>
  </form>
</template>

<script setup lang="ts">
import { reactive } from 'vue'
import { useFinanceStore } from '@/stores/financeStore'

const emit = defineEmits<{ saved: [] }>()
const store = useFinanceStore()

const draft = reactive({
  name: '',
  targetAmount: 0,
  currentAmount: 0,
  dueDate: new Date().toISOString().slice(0, 10),
})

function submit() {
  store.addGoal({ ...draft })
  draft.name = ''
  draft.targetAmount = 0
  draft.currentAmount = 0
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
