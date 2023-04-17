import Vue from "vue";
import VueRouter from "vue-router";
import HomeView from "@/views/HomeView.vue";
import Upload from "@/components/Upload";

Vue.use(VueRouter);

export default new VueRouter({
  routes: [
    {
      path: "/",
      component: HomeView,
    },
    {
      path: "/upload",
      name: "Upload",
      component: Upload,
    },
    {
      path: "/music",
      name: "Music",
      component: () => import("@/components/Music"),
    },
    {
      path: "/dashboard",
      name: "Dashboard",
      component: () => import("@/components/Dashboard"),
    },
    {
      path: "/notes",
      name: "Notes",
      component: () => import("@/views/UtilsView")
    }
  ]
})
