<template>
  <section class="finance-dashboard">
    <header class="finance-dashboard__header">
      <div>
        <p class="finance-dashboard__eyebrow">Dashboard financiero</p>
        <h1>Finanzas personales</h1>
      </div>
      <slot name="actions" />
    </header>

    <slot />
  </section>
</template>

<style scoped lang="scss">
.finance-dashboard {
  display: grid;
  gap: 1rem;
}

.finance-dashboard__header {
  display: flex;
  align-items: flex-end;
  justify-content: space-between;
  gap: 1rem;
  padding-bottom: 0.25rem;
  border-bottom: 1px solid #d8dee8;
}

.finance-dashboard__eyebrow {
  margin: 0 0 0.25rem;
  color: #607089;
  font-size: 0.78rem;
  font-weight: 700;
  text-transform: uppercase;
}

h1 {
  margin: 0;
  color: #17243a;
  font-size: 1.75rem;
}

@media (max-width: 720px) {
  .finance-dashboard__header {
    align-items: stretch;
    flex-direction: column;
  }
}
</style>
