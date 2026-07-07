<template>
  <section class="card shadow-sm">
    <div class="card-body">
      <div class="row g-4 align-items-start">
        <div class="col-lg">
          <p class="h5">Archivos a subir</p>
          <div class="d-flex gap-3 align-items-center">
            <input
              type="file"
              ref="fileInput"
              class="form-control"
              @click="total = 0"
              @change="onFilePicked"
            />
            <button class="btn btn-info text-white" @click="send">Enviar</button>
          </div>
          <div class="progress mt-3" role="progressbar" aria-label="Upload progress" :aria-valuenow="total" aria-valuemin="0" aria-valuemax="100">
            <div class="progress-bar" :style="{ width: `${total}%` }">{{ total }}%</div>
          </div>
        </div>
        <div v-if="loaded" class="col-lg-5">
          <img class="img-fluid rounded border" :src="image" alt="Preview" />
        </div>
      </div>
    </div>
  </section>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import api from "@/api";

export default defineComponent({
  name: "UploadView",
  data: () => ({
    image: "",
    loaded: false,
    file: null as File | null,
    total: 0,
  }),
  methods: {
    async send() {
      if (!this.file) {
        return;
      }

      const form = new FormData();
      form.append("file", this.file);

      const onload = (event: { loaded: number; total?: number }) => {
        const total = event.total ?? event.loaded;
        this.total = Math.round((100 * event.loaded) / total);
      };

      const response = await api.upload(form, onload);

      if (response) {
        console.debug('upload complete')
      }
    },
    onFilePicked(event: Event) {
      const target = event.target as HTMLInputElement;
      const file = target.files?.[0];

      if (!file) {
        return;
      }

      this.file = file;

      const fileReader = new FileReader();
      fileReader.onload = () => {
        this.image = String(fileReader.result ?? "");
        this.loaded = true;
      };
      fileReader.readAsDataURL(file);
    },
  },
})
</script>

<style scoped></style>
