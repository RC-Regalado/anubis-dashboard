<template>
  <section class="utils-layout">
    <header class="utils-layout__header">
      <div>
        <p class="utils-layout__eyebrow">Seguimiento personal</p>
        <h1>Habitos y entrenamiento</h1>
      </div>
      <slot name="actions" />
    </header>
    <slot />
  </section>
</template>

<style scoped lang="scss">
.utils-layout {
  display: grid;
  gap: 1rem;
}

.utils-layout__header {
  display: flex;
  justify-content: space-between;
  align-items: flex-end;
  gap: 1rem;
  padding-bottom: 0.25rem;
  border-bottom: 1px solid #d8dee8;
}

.utils-layout__eyebrow {
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
  .utils-layout__header {
    align-items: stretch;
    flex-direction: column;
  }
}
</style>
