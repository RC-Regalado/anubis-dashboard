import video_types from "@/store/types/video";
import audio_types from "@/store/types/audio";
import general_types from "@/store/types/general";

export default {
  ...video_types,
  ...general_types,
  ...audio_types,
};
