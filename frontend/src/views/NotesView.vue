<template>
  <section class="notes">
    <article class="notes__editor panel">
      <div class="panel__head">
        <div>
          <p class="panel__eyebrow">Notas</p>
          <h2 class="panel__title">Bitácora del día</h2>
        </div>
        <button class="btn btn-outline-secondary" type="button" @click="resetForm">+</button>
      </div>

      <form class="notes__form" @submit.prevent="saveNote">
        <label class="field">
          <span>Titulo</span>
          <input
            v-model="draft.title"
            class="form-control"
            placeholder="Seguimiento, Pensamientos, ..."
            required
          />
        </label>

        <label class="field">
          <span>Tipo</span>
          <input
            v-model="draft.tag"
            class="form-control"
            placeholder="database, trabajo, estudios..."
          />
        </label>

        <label class="field field--full">
          <span>Nota</span>
          <textarea v-model="draft.body" class="form-control" rows="12"></textarea>
        </label>

        <label class="notes__pin">
          <input v-model="draft.pinned" type="checkbox" />
          <span>Fijar</span>
        </label>

        <div class="notes__actions">
          <button class="btn btn-primary" type="submit">
            {{ draft.id ? 'Actualizar' : 'Agregar' }}
          </button>
          <button
            class="btn btn-outline-success"
            type="button"
            :disabled="!draft.title"
            @click="syncCurrent"
          >
            Sincronizar
          </button>
        </div>
      </form>
    </article>

    <article class="notes__list panel">
      <div class="panel__head">
        <div>
          <p class="panel__eyebrow">Almacen</p>
          <h2 class="panel__title">Notas</h2>
        </div>
        <span class="notes__count"
          >{{ notes.length }} {{ notes.length == 1 ? 'nota' : 'notas' }}</span
        >
      </div>

      <div v-if="sortedNotes.length" class="notes__cards">
        <button
          v-for="note in sortedNotes"
          :key="note.id"
          class="note-card"
          :class="{ 'note-card--active': draft.id === note.id }"
          type="button"
          @click="selectNote(note.id)"
        >
          <div class="note-card__top">
            <strong>{{ note.title }}</strong>
            <span v-if="note.pinned" class="note-card__pin">Fijada</span>
          </div>
          <p class="note-card__body">{{ note.body || 'No content yet.' }}</p>
          <div class="note-card__meta">
            <span>{{ note.tag || 'General' }}</span>
            <span>{{ formatDate(note.updatedAt) }}</span>
          </div>
          <div class="note-card__actions">
            <span class="btn btn-sm btn-light">Editar</span>
            <span class="btn btn-sm btn-outline-danger" @click.stop="removeNote(note.id)"
              >Eliminar</span
            >
          </div>
        </button>
      </div>
      <div v-else class="notes__empty">
        Start with a title and body. Notes are persisted locally in this browser.
      </div>
    </article>
  </section>
</template>

<script lang="ts">
import { computed, defineComponent, reactive, ref, watch } from 'vue'
import api from '@/api'

interface NoteItem {
  id: string
  title: string
  tag: string
  body: string
  pinned: boolean
  updatedAt: string
}

const STORAGE_KEY = 'sync-notes'

function loadNotes(): NoteItem[] {
  const raw = localStorage.getItem(STORAGE_KEY)

  if (!raw) {
    return []
  }

  try {
    return JSON.parse(raw) as NoteItem[]
  } catch (error) {
    console.error(error)
    return []
  }
}

function createDraft() {
  return {
    id: '',
    title: '',
    tag: '',
    body: '',
    pinned: false,
  }
}

export default defineComponent({
  name: 'NoteView',
  setup() {
    const notes = ref<NoteItem[]>(loadNotes())
    const draft = reactive(createDraft())

    watch(
      notes,
      (value) => {
        localStorage.setItem(STORAGE_KEY, JSON.stringify(value))
      },
      { deep: true },
    )

    const sortedNotes = computed(() =>
      [...notes.value].sort((left, right) => {
        if (left.pinned !== right.pinned) {
          return left.pinned ? -1 : 1
        }

        return right.updatedAt.localeCompare(left.updatedAt)
      }),
    )

    const resetForm = () => {
      Object.assign(draft, createDraft())
    }

    const saveNote = () => {
      const payload: NoteItem = {
        id: draft.id || `note-${Date.now()}`,
        title: draft.title.trim(),
        tag: draft.tag.trim(),
        body: draft.body.trim(),
        pinned: draft.pinned,
        updatedAt: new Date().toISOString(),
      }

      if (draft.id) {
        notes.value = notes.value.map((note) => (note.id === payload.id ? payload : note))
      } else {
        notes.value.unshift(payload)
      }

      Object.assign(draft, payload)
    }

    const selectNote = (id: string) => {
      const note = notes.value.find((item) => item.id === id)

      if (note) {
        Object.assign(draft, note)
      }
    }

    const removeNote = (id: string) => {
      notes.value = notes.value.filter((note) => note.id !== id)

      if (draft.id === id) {
        resetForm()
      }
    }

    const syncCurrent = async () => {
      if (!draft.title.trim()) {
        return
      }

      const response = await api.saveNote(draft.title.trim(), draft.body.trim())

      if (response) {
        console.debug('note synced')
      }
    }

    const formatDate = (value: string) =>
      new Intl.DateTimeFormat('es-SV', {
        dateStyle: 'medium',
        timeStyle: 'short',
      }).format(new Date(value))

    return {
      draft,
      formatDate,
      notes,
      removeNote,
      resetForm,
      saveNote,
      selectNote,
      sortedNotes,
      syncCurrent,
    }
  },
})
</script>

<style scoped lang="scss">
.notes {
  display: grid;
  grid-template-columns: minmax(0, 1.15fr) minmax(320px, 0.85fr);
  gap: 1.5rem;
}

.panel {
  padding: 1.4rem;
  border-radius: 1.5rem;
  background: var(--panel-bg);
  border: 1px solid var(--panel-border);
  box-shadow: 0 18px 50px rgba(16, 35, 61, 0.08);
  backdrop-filter: blur(18px);
}

.panel__head {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
  align-items: center;
  margin-bottom: 1.25rem;
}

.panel__eyebrow {
  margin: 0 0 0.35rem;
  color: var(--accent);
  text-transform: uppercase;
  letter-spacing: 0.14em;
  font-size: 0.75rem;
  font-weight: 700;
}

.panel__title {
  margin: 0;
  font-size: 1.5rem;
}

.notes__form {
  display: grid;
  grid-template-columns: repeat(2, minmax(0, 1fr));
  gap: 1rem;
}

.field {
  display: grid;
  gap: 0.45rem;
}

.field span {
  font-weight: 600;
}

.field--full {
  grid-column: 1 / -1;
}

.notes__pin {
  display: inline-flex;
  align-items: center;
  gap: 0.6rem;
  font-weight: 600;
}

.notes__actions {
  display: flex;
  gap: 0.75rem;
  grid-column: 1 / -1;
}

.notes__count {
  color: var(--ink-soft);
  font-weight: 600;
}

.notes__cards {
  display: grid;
  gap: 0.9rem;
}

.note-card {
  width: 100%;
  padding: 1rem;
  border: 1px solid rgba(16, 35, 61, 0.08);
  border-radius: 1.1rem;
  background: #ffffff;
  text-align: left;
}

.note-card--active {
  border-color: rgba(17, 122, 101, 0.28);
  box-shadow: 0 12px 30px rgba(17, 122, 101, 0.08);
}

.note-card__top,
.note-card__meta,
.note-card__actions {
  display: flex;
  justify-content: space-between;
  gap: 0.75rem;
  align-items: center;
}

.note-card__pin {
  color: var(--accent-deep);
  font-size: 0.8rem;
  font-weight: 700;
}

.note-card__body {
  margin: 0.85rem 0;
  color: var(--ink-soft);
  line-height: 1.5;
  display: -webkit-box;
  -webkit-box-orient: vertical;
  overflow: hidden;
  -webkit-line-clamp: 3;
}

.note-card__meta {
  color: var(--ink-soft);
  font-size: 0.85rem;
}

.notes__empty {
  padding: 2rem 1rem;
  text-align: center;
  color: var(--ink-soft);
}

@media (max-width: 991px) {
  .notes {
    grid-template-columns: 1fr;
  }
}

@media (max-width: 767px) {
  .panel__head,
  .notes__actions {
    flex-direction: column;
    align-items: stretch;
  }

  .notes__form {
    grid-template-columns: 1fr;
  }
}
</style>
