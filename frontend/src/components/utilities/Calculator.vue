<template>
  <div class="calculator">
    <div class="display">{{ result }}</div>
    <div class="buttons">
      <button v-for="button in buttons" :key="button" @click="handleClick(button)">{{ button }}</button>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      result: "0",
      buttons: ["C", "(", ")", "/", "7", "8", "9", "*", "4", "5", "6", "-", "1", "2", "3", "+", "±", "0", ".", "="],
    };
  },
  methods: {
    handleClick(button) {
      switch (button) {
        case "C":
          this.result = "0";
          break;
        case "=":
          try {
            this.result = eval(this.result);
          } catch (e) {
            this.result = "Error";
          }
          break;
        case "±":
          this.result = eval(-1 * this.result);
          break;
        default:
          if (this.result === "0" || this.result === "Error") {
            this.result = button;
          } else {
            this.result += button;
          }
      }
    },
  },
};
</script>

<style>
.calculator {
  width: 240px;
  height: 300px;
  margin: 0 auto;
  border: 1px solid black;
  border-radius: 10px;
  box-shadow: 5px 5px 5px rgba(0, 0, 0, 0.5);
  display: flex;
  flex-direction: column;
  justify-content: space-between;
}

.display {
  height: 60px;
  border: 1px solid black;
  border-radius: 10px;
  box-shadow: 2px 2px 2px rgba(0, 0, 0, 0.2);
  display: flex;
  justify-content: flex-end;
  align-items: center;
  font-size: 30px;
  padding: 0 10px;
  background-color: #ffffff;
}

.buttons {
  display: grid;
  grid-template-columns: repeat(4, 1fr);
  grid-gap: 5px;
  padding: 10px;
}

button {
  font-size: 20px;
  border-radius: 10px;
  border: none;
  box-shadow: 2px 2px 2px rgba(0, 0, 0, 0.2);
  background-color: #ffffff;
  cursor: pointer;
}

button:hover {
  background-color: #f2f2f2;
}

button:active {
  box-shadow: none;
  transform: translateY(2px);
}
</style>

