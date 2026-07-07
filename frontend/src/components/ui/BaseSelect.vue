<template>
  <label class="base-select">
    <span v-if="label">{{ label }}</span>
    <select :value="modelValue" class="form-select" @change="emitValue">
      <option v-if="placeholder" value="">{{ placeholder }}</option>
      <option v-for="option in options" :key="option.value" :value="option.value">
        {{ option.label }}
      </option>
    </select>
  </label>
</template>

<script setup lang="ts">
interface SelectOption {
  label: string
  value: string
}

defineProps<{
  label?: string
  modelValue: string
  options: SelectOption[]
  placeholder?: string
}>()

const emit = defineEmits<{
  'update:modelValue': [value: string]
}>()

function emitValue(event: Event) {
  emit('update:modelValue', (event.target as HTMLSelectElement).value)
}
</script>

<style scoped lang="scss">
.base-select {
  display: grid;
  gap: 0.35rem;
}

.base-select span {
  color: #334155;
  font-weight: 700;
}
</style>
