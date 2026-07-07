<template>
  <form class="finance-form" @submit.prevent="submit">
    <BaseSelect v-model="draft.categoryId" label="Categoria" :options="categoryOptions" />

    <label class="field">
      <span>Mes</span>
      <input v-model="draft.month" class="form-control" type="month" required />
    </label>

    <label class="field">
      <span>Limite</span>
      <input v-model.number="draft.limitAmount" class="form-control" type="number" min="0" step="0.01" required />
    </label>

    <footer class="finance-form__actions">
      <button class="btn btn-primary" type="submit">Guardar presupuesto</button>
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
  categoryId: 'cat-food',
  month: new Date().toISOString().slice(0, 7),
  limitAmount: 0,
})

const categoryOptions = computed(() =>
  store.state.categories.map((category) => ({ label: category.name, value: category.id })),
)

function submit() {
  store.addBudget({ ...draft })
  draft.limitAmount = 0
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
