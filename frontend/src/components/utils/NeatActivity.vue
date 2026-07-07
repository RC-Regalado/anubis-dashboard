<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Actividad diaria</h2>
    </header>
    <div class="neat-grid">
      <article>
        <span>Pasos promedio</span>
        <strong>{{ Math.round(metrics.averageSteps) }}</strong>
      </article>
      <article>
        <span>Distancia actual</span>
        <strong>{{ latestDay?.distanceKm.toFixed(1) ?? '-' }} km</strong>
      </article>
      <article>
        <span>Tiempo activo</span>
        <strong>{{ latestDay?.activeMinutes ?? '-' }} min</strong>
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

.panel__header h2 {
  margin: 0 0 1rem;
  font-size: 1rem;
}

.neat-grid {
  display: grid;
  gap: 0.75rem;
}

.neat-grid article {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
  padding: 0.75rem;
  border-radius: 8px;
  background: #f6f8fb;
}

.neat-grid span {
  color: #607089;
}
</style>
