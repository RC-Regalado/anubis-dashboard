<template>
  <div>
    <div class="files">
      <div class="file-row" v-for="(file, key) in files" :key="key">
        <p>{{ file["name"] }}</p>
        <div class="item">
          <button id="download" @click="get(file)">Descargar</button>
          <button id="erase" @click="drop(file.hash)">Eliminar</button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import { mapActions } from "vuex";
import types from "@/store/types";
import api from "@/api";

export default {
  name: "FilesContainer",
  data: () => ({
    fields: [
      { key: "name", label: "Archivo" },
      { key: "download", label: "" },
    ],
    files: [],
  }),
  mounted() {
    api
      .requestFiles()
      .then((response) => {
        this.files = response.data;
      })
      .catch((err) => {
        console.error(err);
      });
  },
  methods: {
    get(file) {
      this.request(file);
    },
    drop(hash){
      console.debug(hash);
    },
    ...mapActions([types.request]),
  },
};
</script>

<style lang="scss" scoped>
.files {
  display: flex;
  flex-wrap: wrap;

  .file-row {
    width: 100%;
    box-sizing: border-box;
    padding: 10px;

    @media (min-width: 768px) {
      display: flex;
      justify-content: space-between;
    }

    p {
      overflow-wrap: break-word;
      word-wrap: break-word;
    }

    .item {
      display: flex;

      button {
        margin: 0 10px;
      }
    }
  }
}
</style>
