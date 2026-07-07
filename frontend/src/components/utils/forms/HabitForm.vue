<template>
  <form class="utils-form" @submit.prevent="submit">
    <label class="field">
      <span>Habito</span>
      <input v-model="draft.name" class="form-control" required />
    </label>
    <label class="field">
      <span>Objetivo</span>
      <input v-model="draft.target" class="form-control" placeholder="8000 pasos, 3L agua..." required />
    </label>
    <footer class="utils-form__actions">
      <button class="btn btn-primary" type="submit">Guardar habito</button>
    </footer>
  </form>
</template>

<script setup lang="ts">
import { reactive } from 'vue'
import { useUtilsStore } from '@/stores/utilsStore'

const emit = defineEmits<{ saved: [] }>()
const { addHabit } = useUtilsStore()

const draft = reactive({
  name: '',
  target: '',
})

function submit() {
  addHabit({ ...draft })
  draft.name = ''
  draft.target = ''
  emit('saved')
}
</script>

<style scoped lang="scss">
.utils-form {
  display: grid;
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
  display: flex;
  justify-content: flex-end;
}
</style>
