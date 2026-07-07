<template>
  <Teleport to="body">
    <div v-if="modelValue" class="modal-backdrop" @click.self="close">
      <section class="modal-panel" role="dialog" aria-modal="true" :aria-label="title">
        <header class="modal-panel__header">
          <h2>{{ title }}</h2>
          <button class="modal-panel__close" type="button" title="Cerrar" @click="close">x</button>
        </header>
        <slot />
      </section>
    </div>
  </Teleport>
</template>

<script setup lang="ts">
defineProps<{
  modelValue: boolean
  title: string
}>()

const emit = defineEmits<{
  'update:modelValue': [value: boolean]
}>()

function close() {
  emit('update:modelValue', false)
}
</script>

<style scoped lang="scss">
.modal-backdrop {
  position: fixed;
  inset: 0;
  z-index: 1000;
  display: grid;
  place-items: center;
  padding: 1rem;
  background: rgba(15, 23, 42, 0.38);
}

.modal-panel {
  width: min(760px, 100%);
  max-height: min(88vh, 860px);
  overflow: auto;
  padding: 1.25rem;
  border-radius: 8px;
  background: #ffffff;
  box-shadow: 0 24px 70px rgba(15, 23, 42, 0.28);
}

.modal-panel__header {
  display: flex;
  align-items: center;
  justify-content: space-between;
  gap: 1rem;
  margin-bottom: 1rem;
}

.modal-panel__header h2 {
  margin: 0;
  font-size: 1.25rem;
}

.modal-panel__close {
  width: 2rem;
  height: 2rem;
  border: 1px solid #cbd5e1;
  border-radius: 50%;
  background: #ffffff;
  color: #334155;
  line-height: 1;
}
</style>
