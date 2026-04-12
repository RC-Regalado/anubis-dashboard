<template>
  <section class="files card shadow-sm">
    <div class="card-body">
      <div v-for="file in files" :key="file.hash" class="file-row">
        <p>{{ file.name }}</p>
        <div class="item">
          <button id="download" class="btn btn-primary btn-sm" @click="get(file)">Descargar</button>
          <button id="erase" class="btn btn-outline-danger btn-sm" @click="drop(file.hash)">
            Eliminar
          </button>
        </div>
      </div>
    </div>
  </section>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import types from '@/store/types'
import api, { FileItem } from '@/api'

import download from 'downloadjs'

export default defineComponent({
  name: 'FilesContainer',
  data: () => ({
    files: [] as FileItem[],
  }),
  async mounted() {
    const response = await api.requestFiles()

    if (response) {
      this.files = response
    }
  },
  methods: {
    async get(file: FileItem) {
      const resp = await api.requestFile(file.hash)

      if (!resp) {
        return
      }

      download(resp, file.name)
    },
    drop(hash: string) {
      console.debug(hash)
    },
  },
})
</script>

<style lang="scss" scoped>
.files {
  display: flex;
  flex-wrap: wrap;
  border: 0;
  border-radius: 1.5rem;
  background: var(--panel-bg);
  border: 1px solid var(--panel-border);
  backdrop-filter: blur(20px);

  .file-row {
    width: 100%;
    box-sizing: border-box;
    padding: 10px;
    border-bottom: 1px solid #e9ecef;

    @media (min-width: 768px) {
      display: flex;
      justify-content: space-between;
      align-items: center;
    }

    p {
      margin-bottom: 0.5rem;
      overflow-wrap: break-word;
      word-wrap: break-word;
      font-weight: 600;
    }

    .item {
      display: flex;
      gap: 0.75rem;

      button {
        margin: 0;
      }
    }
  }

  .file-row:last-child {
    border-bottom: 0;
  }
}
</style>
