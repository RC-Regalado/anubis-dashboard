<template>
  <div id="app">
    <header>
      <nav-bar class="full"></nav-bar>
    </header>
    <b-container>
      <router-view />
    </b-container>
  </div>
</template>

<script>
import { mapActions } from "vuex";
import types from "@/store/types";
import NavBar from "@/components/NavBar";

export default {
  name: "main-entry",
  components: { NavBar },
  mounted() {
    this.data();
    this.readCurses();
  },
  methods: {
    ...mapActions([types.data, types.readCurses, types.requestMusic]),
  },
};
</script>
<style lang="scss">
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  //text-align: center;
  color: #2c3e50;
}

#nav {
  padding: 30px;

  a {
    font-weight: bold;
    color: #2c3e50;

    &.router-link-exact-active {
      color: #42b983;
    }
  }
}

.full {
  width: calc(100%);
}
</style>
