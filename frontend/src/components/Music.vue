<template>
  <div>
    <audio
      ref="player"
      @ended="onEnd"
      @canplay="onCanPlay"
      :src="currentSongSource"
      controls
      class="w-100 mb-4"
    >
      <p>Error</p>
    </audio>

    <div class="card shadow-sm">
      <div class="table-responsive">
        <table class="table table-hover align-middle mb-0">
          <thead>
            <tr>
              <th scope="col">Cancion</th>
              <th scope="col" class="text-end">Accion</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="song in songs" :key="`${song.path}-${song.name}`">
              <td>{{ song.name }}</td>
              <td class="text-end">
                <button class="btn btn-success btn-sm" @click="play(song)">Play</button>
              </td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import api from '@/api'
import type { Song } from '@/api'

export default defineComponent({
  name: 'MusicView',
  data: () => ({
    index: -1,
    currentSong: null as Song | null,
    songs: [] as Song[],
  }),
  async mounted() {
    const songs = await api.requestMusic()

    if (songs) {
      this.songs = songs
    }
  },
  computed: {
    currentSongSource(): string {
      if (!this.currentSong) {
        return ''
      }

      return `${this.currentSong.path}${this.currentSong.name}`
    },
  },
  methods: {
    onEnd() {
      if (!this.songs.length) {
        return
      }

      if (this.index >= this.songs.length - 1) {
        this.index = 0
      } else {
        this.index += 1
      }

      this.currentSong = this.songs[this.index] ?? null
      const player = this.$refs.player as HTMLAudioElement | undefined
      player?.load()
    },
    play(song: Song) {
      this.currentSong = song
      this.index = this.songs.indexOf(song)
    },
    onCanPlay() {
      const player = this.$refs.player as HTMLAudioElement | undefined
      player?.play()
    },
  },
  watch: {
    currentSong() {
      if (this.index >= 0) {
        const player = this.$refs.player as HTMLAudioElement | undefined
        player?.play()
      }
    },
  },
})
</script>

<style scoped>
.table td,
.table th {
  vertical-align: middle;
}
</style>
