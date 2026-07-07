<template>
  <section class="summary-grid">
    <StatCard label="Peso promedio semanal" :value="`${metrics.weeklyAverageWeight.toFixed(1)} kg`" tone="balance" />
    <StatCard label="Tendencia cintura" :value="`${metrics.waistTrend.toFixed(1)} cm`" :tone="metrics.waistTrend <= 0 ? 'savings' : 'expense'" />
    <StatCard label="FCR promedio" :value="`${Math.round(metrics.averageRecoveryHeartRate)} bpm`" tone="income" />
    <StatCard label="RHR promedio" :value="`${Math.round(metrics.averageRestingHeartRate)} bpm`" tone="neutral" />
    <StatCard label="Sueno promedio" :value="`${metrics.averageSleepHours.toFixed(1)} h`" tone="savings" />
    <StatCard label="Consistencia" :value="`${Math.round(metrics.trainingConsistency)}%`" tone="balance" />
  </section>
</template>

<script setup lang="ts">
import StatCard from '@/components/ui/StatCard.vue'
import { useUtilsStore } from '@/stores/utilsStore'

const { metrics } = useUtilsStore()
</script>

<style scoped lang="scss">
.summary-grid {
  display: grid;
  grid-template-columns: repeat(6, minmax(0, 1fr));
  gap: 0.85rem;
}

@media (max-width: 1280px) {
  .summary-grid {
    grid-template-columns: repeat(3, minmax(0, 1fr));
  }
}

@media (max-width: 720px) {
  .summary-grid {
    grid-template-columns: 1fr;
  }
}
</style>
