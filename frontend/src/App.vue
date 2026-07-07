<template>
  <div id="app" class="app-shell">
    <NavBar class="sidebar-shell" />
    <main class="content-shell">
      <router-view />
    </main>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import NavBar from '@/components/NavBar.vue'

export default defineComponent({
  name: 'main-entry',
  components: { NavBar },
})
</script>
<style lang="scss">
:root {
  --app-bg: #eef2f7;
  --panel-bg: rgba(255, 255, 255, 0.92);
  --panel-border: rgba(64, 84, 110, 0.12);
  --ink-strong: #10233d;
  --ink-soft: #5d6b80;
  --accent: #117a65;
  --accent-deep: #0c5a49;
  --sidebar-bg: linear-gradient(180deg, #10233d 0%, #162f54 52%, #1a4067 100%);
}

#app {
  font-family: 'Segoe UI', 'Helvetica Neue', Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  color: var(--ink-strong);
}

.app-shell {
  min-height: 100vh;
  display: grid;
  grid-template-columns: 290px minmax(0, 1fr);
  background:
    radial-gradient(circle at top left, rgba(17, 122, 101, 0.12), transparent 28%),
    radial-gradient(circle at bottom right, rgba(16, 35, 61, 0.12), transparent 32%), var(--app-bg);
}

.content-shell {
  min-width: 0;
  padding: 2rem;
}

@media (max-width: 991px) {
  .app-shell {
    grid-template-columns: 1fr;
  }

  .content-shell {
    padding: 1rem;
  }
}
</style>
