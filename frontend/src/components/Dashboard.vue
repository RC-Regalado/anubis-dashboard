<template>
  <b-container>
    <b-row>
      <b-col>
        <p>
          Accion
        </p>
      </b-col>
    </b-row>
    <b-row>
      <b-btn class="btn btn-info" @click="xsetoff"> Apagar pantalla </b-btn>
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
    xsetoff() {
      api.screenOff().then((response) => {
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
