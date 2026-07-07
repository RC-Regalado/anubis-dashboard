<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Relaciones detectadas</h2>
    </header>
    <div class="insight-list">
      <article v-for="insight in relationships" :key="insight.label" class="insight" :class="`insight--${insight.tone}`">
        <strong>{{ insight.label }}</strong>
        <span>{{ insight.value }}</span>
      </article>
    </div>
  </section>
</template>

<script setup lang="ts">
import { useUtilsStore } from '@/stores/utilsStore'

const { relationships } = useUtilsStore()
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

.insight-list {
  display: grid;
  gap: 0.75rem;
}

.insight {
  display: grid;
  gap: 0.25rem;
  padding: 0.85rem;
  border-left: 4px solid #315fbc;
  border-radius: 8px;
  background: #f6f8fb;
}

.insight span {
  color: #607089;
}

.insight--good {
  border-left-color: #168a52;
}

.insight--warn {
  border-left-color: #c2413d;
}
</style>
