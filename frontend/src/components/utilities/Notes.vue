<template>
  <div>
    <b-form @submit.prevent="submitForm">
      <b-form-group id="input-group-1" label="Nombre:" label-for="input-1">
        <b-form-input id="input-1" v-model="nombre" required></b-form-input>
      </b-form-group>

      <b-form-group id="textarea-group-1" label="Valor:" label-for="textarea-1">
        <b-form-textarea id="textarea-1" v-model="valor" rows="6" max-rows="6"></b-form-textarea>
      </b-form-group>

      <b-button type="submit" variant="primary">Enviar</b-button>
    </b-form>
  </div>
</template>

<script>
import api from "@/api";

export default {
  name: "NotePad",
  data() {
    return {
      nombre: '',
      valor: ''
    }
  },
  methods: {
    submitForm() {
      if (this.nombre !== ""){
        api.saveNote(this.nombre, this.valor).then((response) => {
          console.debug(response);
        });
      }
    }
  }
}
</script>

