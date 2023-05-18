<template>
  <div>
    <audio
      ref="player"
      @ended="onEnd"
      @canplay="onCanPlay"
      :src="currentSong.path + currentSong.name"
      controls
    >
      <p>Error</p>
    </audio>

    <b-table :items="songs" :fields="fields">
      <template #cell(play)="row">
        <b-btn variant="success" v-on:click="play(row.item)" class="mr-1">
          <b-icon-play-btn />
        </b-btn>
      </template>
    </b-table>
  </div>
</template>

<script>
import { mapState } from "vuex";
import { requestMusic } from "@/api";

export default {
  name: "MusicView",
  data: () => ({
    index: -1,
    fields: [
      { key: "name", label: "Canción" },
      { key: "play", label: "" },
    ],
    currentSong: {
      name: "",
      mime: "",
    },
  }),
  mounted() {
    requestMusic()
  },
  methods: {
    onEnd() {
      if (this.index > this.songs.length) this.index = 0;

      this.currentSong = this.songs[++this.index];

      this.$refs.player.load();
    },
    play(song) {
      this.currentSong = song;
      this.index = this.songs.indexOf(song);
    },
    onCanPlay() {
      this.$refs.player.play();
    },
  },
  computed: {
    ...mapState({
      songs: (state) => state.app.songs,
    }),
  },
  watch: {
    currentSong() {
      if (this.index > 0) {
        this.$refs.player.play();
      }
    },
  },
};
</script>

<style scoped></style>
