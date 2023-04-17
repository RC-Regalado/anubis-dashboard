<template>
  <div>
    <b-table :items="files" :fields="fields">
      <template #cell(download)="row">
        <b-btn variant="success" v-on:click="get(row.item)" class="mr-1">
          Descargar
        </b-btn>
      </template>
    </b-table>
  </div>
</template>

<script>
import { mapState, mapActions } from "vuex";
import types from "@/store/types";

export default {
  name: "FilesContainer",
  data: () => ({
    fields: [
      { key: "name", label: "Archivo" },
      { key: "download", label: "" },
    ],
  }),
  computed: {
    ...mapState({
      files: (state) => state.app.files,
    }),
  },
  methods: {
    get(file) {
      this.request(file);
    },
    ...mapActions([types.request]),
  },
};
</script>
