<template>
  <div>
    <b-navbar toggleable="lg" type="dark" class="transparent">
      <b-navbar-brand href="/">R</b-navbar-brand>

      <b-navbar-toggle target="nav-collapse"></b-navbar-toggle>

      <b-collapse id="nav-collapse" is-nav>
        <b-navbar-nav>
          <b-nav-item to="/">Home</b-nav-item>
          <b-nav-item to="/upload">Upload</b-nav-item>
          <b-nav-item to="/music">Music</b-nav-item>
          <b-nav-item to="/dashboard">Dashboard</b-nav-item>
          <b-nav-item to="/notes">Notes</b-nav-item>
        </b-navbar-nav>

        <!-- Right aligned nav items -->
        <b-navbar-nav class="ml-auto">
          <b-nav-form>
            <b-form-input
              size="sm"
              className="mr-sm-2"
              placeholder="Search"
            ></b-form-input>
            <b-button size="sm" class="my-2 my-sm-0" type="submit"
              >Search
            </b-button>
          </b-nav-form>
        </b-navbar-nav>
      </b-collapse>
    </b-navbar>
  </div>
</template>

<script>
export default {
  name: "nav-bar",
};
</script>

<style scoped>
.transparent {
  background: #2c3e50;
  color: #ffffff !important;
}
</style>
