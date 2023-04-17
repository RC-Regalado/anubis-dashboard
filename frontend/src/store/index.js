import Vue from "vue";
import Vuex from "vuex";
import api from "@/api";
import types from "@/store/types";
import download from "downloadjs";
Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    app: {
      files: [],
      curses: [],
      songs: [],
      downloadFile: "",
    },
    curse: {
      video: "",
      chapters: [],
    },
  },
  mutations: {
    [types.addFile]: function (state, file) {
      state.app.files.push(file);
    },
    [types.addCurse]: function (state, payload) {
      state.app.curses.push({
        id: payload.id,
        name: payload.name,
      });
    },
    [types.setDownloadTarget]: function (state, payload) {
      state.app.downloadFile = payload;
    },
    [types.addSong]: function (state, payload) {
      state.app.songs.push(payload);
    },
  },
  actions: {
    [types.data]: async function ({ commit }) {
      const files = await api.requestFiles();
      for (let i = 0; i < files.data.length; i++) {
        commit(types.addFile, files.data[i]);
      }
    },
    [types.readCurses]: async function ({ commit }) {
      const curses = await api.requestCurses();

      for (let i = 0; i < curses.data.length; i++) {
        commit(types.addCurse, {
          id: i,
          name: curses.data[i],
        });
      }
    },
    [types.request]: async function ({ commit, getters }, file) {
      commit(types.setDownloadTarget, file);
      const target = getters.getTarget;
      const resp = await api.requestFile(target);

      console.debug(resp.data);
      download(resp.data, file.name);
    },
    [types.requestMusic]: async function ({ commit }) {
      const songs = await api.requestMusic();

      if (songs)
        for (let i = 0; i < songs.data.length; i++) {
          commit(types.addSong, songs.data[i]);
        }
    },
  },
  getters: {
    [types.getTarget]: function (state) {
      return state.app.downloadFile;
    },
  },
  modules: {},
});
