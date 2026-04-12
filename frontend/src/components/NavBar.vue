<template>
  <aside class="sidebar">
    <div class="sidebar__top">
      <div>
        <p class="sidebar__eyebrow">Sync Console</p>
        <RouterLink class="sidebar__brand" to="/">Anubis</RouterLink>
      </div>
      <button
        class="sidebar__toggle"
        type="button"
        aria-label="Toggle navigation"
        @click="isOpen = !isOpen"
      >
        Menu
      </button>
    </div>

    <div class="sidebar__body" :class="{ 'sidebar__body--open': isOpen }">
      <nav class="sidebar__nav">
        <RouterLink
          v-for="item in navItems"
          :key="item.to"
          class="sidebar__link"
          :to="item.to"
          @click="isOpen = false"
        >
          <span class="sidebar__label">{{ item.label }}</span>
          <small class="sidebar__caption">{{ item.caption }}</small>
        </RouterLink>
      </nav>

      <section class="sidebar__spotlight">
        <p class="sidebar__spotlight-title">{{ date }}</p>
        <p class="sidebar__spotlight-copy"></p>
      </section>
    </div>
  </aside>
</template>

<script lang="ts">
import { defineComponent } from 'vue'

export default defineComponent({
  name: 'nav-bar',
  data() {
    return {
      isOpen: false,
      navItems: [
        { to: '/', label: 'Dashboard', caption: '----' },
        { to: '/file', label: 'Files', caption: 'Documentos' },
        { to: '/notes', label: 'Notes', caption: 'Agenda' },
        { to: '/upload', label: 'Upload', caption: 'Subir archivo' },
        { to: '/music', label: 'Music', caption: 'Música' },
      ],
      date: '',
      todInterval: 0,
    }
  },
  mounted() {
    this.setDate()
    this.todInterval = setInterval(() => {
      this.setDate()
    }, 1000 * 60)
  },
  unmounted() {
    if (this.todInterval) clearInterval(this.todInterval)
    this.todInterval = 0
  },
  methods: {
    setDate() {
      this.date = new Intl.DateTimeFormat('es-SV', {
        dateStyle: 'medium',
        timeStyle: 'short',
      }).format(new Date().Now)
    },
  },
})
</script>

<style scoped lang="scss">
.sidebar {
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
  min-height: 100vh;
  padding: 1.75rem 1.25rem;
  background: var(--sidebar-bg);
  color: #f4f7fb;
  border-right: 1px solid rgba(255, 255, 255, 0.08);
}

.sidebar__top {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
  align-items: flex-start;
}

.sidebar__eyebrow {
  margin: 0;
  font-size: 0.78rem;
  letter-spacing: 0.16em;
  text-transform: uppercase;
  color: rgba(255, 255, 255, 0.58);
}

.sidebar__brand {
  display: inline-block;
  margin-top: 0.35rem;
  color: #ffffff;
  font-size: 1.8rem;
  font-weight: 700;
  text-decoration: none;
}

.sidebar__toggle {
  display: none;
  border: 1px solid rgba(255, 255, 255, 0.24);
  background: rgba(255, 255, 255, 0.08);
  color: #ffffff;
  border-radius: 999px;
  padding: 0.5rem 0.9rem;
}

.sidebar__body {
  display: flex;
  flex: 1;
  flex-direction: column;
  justify-content: space-between;
  gap: 1.5rem;
}

.sidebar__nav {
  display: grid;
  gap: 0.75rem;
}

.sidebar__link {
  display: block;
  padding: 0.95rem 1rem;
  border-radius: 1rem;
  color: rgba(255, 255, 255, 0.86);
  text-decoration: none;
  background: rgba(255, 255, 255, 0.06);
  border: 1px solid transparent;
  transition: 160ms ease;
}

.sidebar__link:hover,
.sidebar__link.router-link-active {
  color: #ffffff;
  background: rgba(255, 255, 255, 0.12);
  border-color: rgba(157, 223, 211, 0.24);
  transform: translateX(2px);
}

.sidebar__label {
  display: block;
  font-weight: 600;
}

.sidebar__caption {
  display: block;
  margin-top: 0.15rem;
  color: rgba(255, 255, 255, 0.58);
}

.sidebar__spotlight {
  padding: 1.1rem;
  border-radius: 1.25rem;
  background: linear-gradient(180deg, rgba(255, 255, 255, 0.13), rgba(255, 255, 255, 0.05));
  border: 1px solid rgba(255, 255, 255, 0.09);
}

.sidebar__spotlight-title {
  margin-bottom: 0.45rem;
  font-weight: 700;
}

.sidebar__spotlight-copy {
  margin: 0;
  color: rgba(255, 255, 255, 0.72);
  line-height: 1.5;
}

@media (max-width: 991px) {
  .sidebar {
    min-height: auto;
    padding: 1rem;
    border-right: 0;
    border-bottom: 1px solid rgba(255, 255, 255, 0.08);
  }

  .sidebar__toggle {
    display: inline-flex;
  }

  .sidebar__body {
    display: none;
  }

  .sidebar__body--open {
    display: flex;
  }
}
</style>
