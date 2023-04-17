<template>
  <b-container>
    <b-row>
      <b-col>
        <p>
          Archivos a subir
          <b-icon-upload></b-icon-upload>
        </p>
      </b-col>
      <b-col cols="5" class="mb-0">
        <b-img class="active w-100" :src="image" v-if="loaded" />
      </b-col>
    </b-row>
    <b-row>
      <input
        type="file"
        ref="fileInput"
        v-on:click="total = 0"
        @change="onFilePicked"
      />
      <b-btn class="btn btn-info" @click="send"> Enviar </b-btn>
    </b-row>
    <b-row>
      <b-col sm="12" style="padding-top: 1em">
        <b-progress max="100" class="mb-3" :value="total" />
      </b-col>
    </b-row>
  </b-container>
</template>

<script>
import api from "@/api";

export default {
  name: "UploadView",
  data: () => ({
    image: "",
    loaded: false,
    file: "",
    total: 0,
  }),
  methods: {
    send() {
      let form = new FormData();
      form.append("file", this.file);

      const onload = (e) => {
        this.total = Math.round((100 * e.loaded) / e.total);
        console.debug(e.loaded);
        console.debug();
      };
      api.upload(form, onload).then((response) => {
        console.debug(response.data);
      });
    },
    onFilePicked(event) {
      const file = event.target.files[0];
      this.file = file;

      const fileReader = new FileReader();
      fileReader.onload = () => {
        this.image = fileReader.result;
        this.loaded = true;
        console.debug(this.image);
      };
      fileReader.readAsDataURL(file);
      // this.image = files[0];
    },
  },
};
</script>

<style scoped></style>
