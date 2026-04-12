<template>
  <div class="home">
    <Files />
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import Files from "@/components/Files.vue";

export default defineComponent({
  name: "MainLayout",
  components: {
    Files,
  },
});
</script>
