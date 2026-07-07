<template>
  <form class="utils-form" @submit.prevent="submit">
    <label class="field">
      <span>Fecha</span>
      <input v-model="draft.date" class="form-control" type="date" required />
    </label>
    <BaseSelect v-model="draft.type" label="Comida" :options="typeOptions" />
    <label class="field">
      <span>Proteína g</span>
      <input v-model.number="draft.protein" class="form-control" type="number" min="0" />
    </label>
    <label class="field">
      <span>Carbs g</span>
      <input v-model.number="draft.carbs" class="form-control" type="number" min="0" />
    </label>
    <label class="field">
      <span>Grasas g</span>
      <input v-model.number="draft.fats" class="form-control" type="number" min="0" />
    </label>
    <footer class="utils-form__actions">
      <button class="btn btn-primary" type="submit">Guardar comida</button>
    </footer>
  </form>
</template>

<script setup lang="ts">
import { reactive } from 'vue'
import BaseSelect from '@/components/ui/BaseSelect.vue'
import { useUtilsStore } from '@/stores/utilsStore'
import type { MealInput, MealType } from '@/stores/utilsStore'

const emit = defineEmits<{ saved: [] }>()
const { addMeal } = useUtilsStore()

const draft = reactive<MealInput>({
  date: new Date().toISOString().slice(0, 10),
  type: 'lunch',
  protein: 0,
  carbs: 0,
  fats: 0,
})

const typeOptions: Array<{ label: string; value: MealType }> = [
  { label: 'Desayuno', value: 'breakfast' },
  { label: 'Almuerzo', value: 'lunch' },
  { label: 'Cena', value: 'dinner' },
  { label: 'Snack', value: 'snack' },
]

function submit() {
  addMeal({ ...draft })
  draft.protein = 0
  draft.carbs = 0
  draft.fats = 0
  emit('saved')
}
</script>

<style scoped lang="scss">
.utils-form {
  display: grid;
  grid-template-columns: repeat(2, minmax(0, 1fr));
  gap: 0.85rem;
}

.field {
  display: grid;
  gap: 0.3rem;
}

.field span {
  color: #334155;
  font-weight: 700;
}

.utils-form__actions {
  grid-column: 1 / -1;
  display: flex;
  justify-content: flex-end;
}

@media (max-width: 720px) {
  .utils-form {
    grid-template-columns: 1fr;
  }
}
</style>
