import { ActionContext, createStore } from "vuex";
import download from "downloadjs";
import api, { Course, FileItem, Song } from "@/api";
import types from "@/store/types";

export interface AppState {
  files: FileItem[];
  curses: Course[];
  songs: Song[];
  downloadFile: FileItem | null;
}

export interface RootState {
  app: AppState;
  curse: {
    video: string;
    chapters: string[];
  };
}

type StoreContext = ActionContext<RootState, RootState>;

const store = createStore<RootState>({
  state: {
    app: {
      files: [],
      curses: [],
      songs: [],
      downloadFile: null,
    },
    curse: {
      video: "",
      chapters: [],
    },
  },
  mutations: {
    [types.addFile](state, file: FileItem) {
      state.app.files.push(file);
    },
    [types.addCurse](state, payload: Course) {
      state.app.curses.push({
        id: payload.id,
        name: payload.name,
      });
    },
    [types.setDownloadTarget](state, payload: FileItem | null) {
      state.app.downloadFile = payload;
    },
    [types.addSong](state, payload: Song) {
      state.app.songs.push(payload);
    },
    [types.resetFiles](state) {
      state.app.files = [];
    },
    [types.resetCurses](state) {
      state.app.curses = [];
    },
    [types.resetSongs](state) {
      state.app.songs = [];
    },
  },
  actions: {
    async [types.data]({ commit }: StoreContext) {
      const files = await api.requestFiles();

      if (!files) {
        return;
      }

      commit(types.resetFiles);

      for (const file of files.data) {
        commit(types.addFile, file);
      }
    },
    async [types.readCurses]({ commit }: StoreContext) {
      const curses = await api.requestCurses();

      if (!curses) {
        return;
      }

      commit(types.resetCurses);

      for (const [index, curse] of curses.data.entries()) {
        commit(types.addCurse, {
          id: index,
          name: curse,
        });
      }
    },
    async [types.request]({ commit, getters }: StoreContext, file: FileItem) {
      commit(types.setDownloadTarget, file);
      const target = getters[types.getTarget] as FileItem | null;

      if (!target) {
        return;
      }

      const resp = await api.requestFile(target.hash);

      if (!resp) {
        return;
      }

      download(resp.data, file.name);
    },
    async [types.requestMusic]({ commit }: StoreContext) {
      const songs = await api.requestMusic();

      if (!songs) {
        return;
      }

      commit(types.resetSongs);

      for (const song of songs.data) {
        commit(types.addSong, song);
      }
    },
  },
  getters: {
    [types.getTarget](state): FileItem | null {
      return state.app.downloadFile;
    },
  },
});

export default store;
