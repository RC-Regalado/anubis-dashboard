<template>
  <section class="view-shell">
    <div class="view-shell__header">
      <div>
        <p class="view-shell__eyebrow">Library</p>
        <h1 class="view-shell__title">Files</h1>
      </div>
    </div>
    <Files />
  </section>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import Files from '@/components/Files.vue'

export default defineComponent({
  name: 'FilesView',
  components: {
    Files,
  },
})
</script>

<style scoped lang="scss">
.view-shell {
  display: grid;
  gap: 1.5rem;
}

.view-shell__header {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
  align-items: flex-end;
  flex-wrap: wrap;
}

.view-shell__eyebrow {
  margin: 0 0 0.35rem;
  color: var(--accent);
  font-size: 0.78rem;
  font-weight: 700;
  letter-spacing: 0.12em;
  text-transform: uppercase;
}

.view-shell__title {
  margin: 0;
  font-size: clamp(2rem, 4vw, 2.8rem);
}

.view-shell__subtitle {
  max-width: 36rem;
  margin: 0;
  color: var(--ink-soft);
}
</style>
