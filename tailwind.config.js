/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "./*.html",
    "./src/public/*.html",
    "./src/views/*.ejs",
    "./dist/public/*.html",
    "./src/**/*.{html,js,ejs,ts}",
  ],
  theme: {
    extend: {},
  },
  plugins: [],
};