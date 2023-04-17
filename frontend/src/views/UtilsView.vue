<template>
  <b-container class="home">
    <notes></notes>
  </b-container>
</template>

<script>
// @ is an alias to /src
import Notes from "@/components/utilities/Notes";

export default {
  name: "UtilsView",
  components: {
    Notes,
  },
};
</script>
