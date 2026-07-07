<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Metricas fisiologicas</h2>
      <span>{{ latestDay?.date ?? '-' }}</span>
    </header>
    <div class="metrics-list">
      <article>
        <span>Presion arterial</span>
        <strong>{{ metrics.latestBloodPressure }}</strong>
      </article>
      <article>
        <span>Peso actual</span>
        <strong>{{ metrics.latestWeight.toFixed(1) }} kg</strong>
      </article>
      <article>
        <span>Cintura</span>
        <strong>{{ latestDay?.waist.toFixed(1) ?? '-' }} cm</strong>
      </article>
      <article>
        <span>Pecho / muslo</span>
        <strong>{{ latestDay ? `${latestDay.chest} / ${latestDay.thigh} cm` : '-' }}</strong>
      </article>
    </div>
  </section>
</template>

<script setup lang="ts">
import { useUtilsStore } from '@/stores/utilsStore'

const { latestDay, metrics } = useUtilsStore()
</script>

<style scoped lang="scss">
.panel {
  padding: 1rem;
  border: 1px solid #d8dee8;
  border-radius: 8px;
  background: #ffffff;
}

.panel__header {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
  margin-bottom: 1rem;
}

.panel__header h2 {
  margin: 0;
  font-size: 1rem;
}

.panel__header span,
.metrics-list span {
  color: #607089;
}

.metrics-list {
  display: grid;
  grid-template-columns: repeat(2, minmax(0, 1fr));
  gap: 0.75rem;
}

.metrics-list article {
  display: grid;
  gap: 0.2rem;
  padding: 0.85rem;
  border-radius: 8px;
  background: #f6f8fb;
}

@media (max-width: 720px) {
  .metrics-list {
    grid-template-columns: 1fr;
  }
}
</style>
