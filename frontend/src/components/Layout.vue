<template>
  <b-container class="home">
    <files></files>
  </b-container>
</template>

<script>
// @ is an alias to /src
import Files from "@/components/Files";

export default {
  name: "MainLayout",
  components: {
    Files,
  },
};
</script>
