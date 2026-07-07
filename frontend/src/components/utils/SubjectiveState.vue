<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Estado subjetivo</h2>
    </header>
    <div class="state-list">
      <article v-for="item in subjectiveLoad" :key="item.date" class="state-row">
        <strong>{{ item.date.slice(5) }}</strong>
        <span>E {{ item.energy }}</span>
        <span>Est {{ item.stress }}</span>
        <span>DOMS {{ item.doms }}</span>
        <span>Dolor {{ item.pain }}</span>
        <span>Mot {{ item.motivation }}</span>
      </article>
    </div>
  </section>
</template>

<script setup lang="ts">
import { useUtilsStore } from '@/stores/utilsStore'

const { subjectiveLoad } = useUtilsStore()
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

.state-list {
  display: grid;
  gap: 0.5rem;
}

.state-row {
  display: grid;
  grid-template-columns: 64px repeat(5, minmax(42px, 1fr));
  gap: 0.5rem;
  align-items: center;
  padding: 0.65rem;
  border-radius: 8px;
  background: #f6f8fb;
}

.state-row span {
  color: #607089;
  font-size: 0.86rem;
}

@media (max-width: 720px) {
  .state-row {
    grid-template-columns: repeat(2, minmax(0, 1fr));
  }
}
</style>
