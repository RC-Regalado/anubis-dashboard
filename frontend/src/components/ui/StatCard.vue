<template>
  <article class="stat-card" :class="`stat-card--${tone}`">
    <span class="stat-card__label">{{ label }}</span>
    <strong class="stat-card__value">{{ value }}</strong>
    <small v-if="detail" class="stat-card__detail">{{ detail }}</small>
  </article>
</template>

<script setup lang="ts">
withDefaults(
  defineProps<{
    label: string
    value: string
    detail?: string
    tone?: 'balance' | 'income' | 'expense' | 'savings' | 'debt' | 'neutral'
  }>(),
  {
    detail: '',
    tone: 'neutral',
  },
)
</script>

<style scoped lang="scss">
.stat-card {
  min-height: 112px;
  padding: 1rem;
  border: 1px solid #d8dee8;
  border-radius: 8px;
  background: #ffffff;
  display: grid;
  align-content: space-between;
  gap: 0.75rem;
}

.stat-card__label {
  color: #607089;
  font-size: 0.82rem;
  font-weight: 700;
  text-transform: uppercase;
}

.stat-card__value {
  color: #17243a;
  font-size: 1.55rem;
  line-height: 1.15;
}

.stat-card__detail {
  color: #607089;
}

.stat-card--income {
  border-top: 4px solid #168a52;
}

.stat-card--expense,
.stat-card--debt {
  border-top: 4px solid #c2413d;
}

.stat-card--savings {
  border-top: 4px solid #1f7a8c;
}

.stat-card--balance {
  border-top: 4px solid #315fbc;
}
</style>
