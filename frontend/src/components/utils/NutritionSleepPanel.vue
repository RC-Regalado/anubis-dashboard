<template>
  <section class="panel">
    <header class="panel__header">
      <h2>Nutricion y sueno</h2>
    </header>
    <div class="nutrition-grid">
      <article>
        <span>Calorias promedio</span>
        <strong>{{ Math.round(metrics.averageCalories) }} kcal</strong>
      </article>
      <article>
        <span>Proteina promedio</span>
        <strong>{{ Math.round(metrics.averageProtein) }} g</strong>
      </article>
      <article>
        <span>Azucar simple</span>
        <strong>{{ Math.round(metrics.averageSugar) }} g</strong>
      </article>
      <article>
        <span>Agua</span>
        <strong>{{ metrics.averageWater.toFixed(1) }} L</strong>
      </article>
      <article>
        <span>Calidad sueno</span>
        <strong>{{ latestDay?.sleepQuality ?? '-' }}/5</strong>
      </article>
      <article>
        <span>Despertares</span>
        <strong>{{ latestDay?.nightlyWakeups ?? '-' }}</strong>
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

.nutrition-grid {
  display: grid;
  grid-template-columns: repeat(2, minmax(0, 1fr));
  gap: 0.75rem;
}

.nutrition-grid article {
  display: grid;
  gap: 0.2rem;
  padding: 0.85rem;
  border-radius: 8px;
  background: #f6f8fb;
}

.nutrition-grid span {
  color: #607089;
}

@media (max-width: 720px) {
  .nutrition-grid {
    grid-template-columns: 1fr;
  }
}
</style>
