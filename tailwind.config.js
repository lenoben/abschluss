/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "./*.html",
    "./src/public/*.html",
    "./src/views/*.ejs",
    "./dist/public/*.html",
    "./src/**/*.{html,js,ejs,ts}",
    
    "./Server/*.html",
    "./Server/src/public/*.html",
    "./Server/src/views/*.ejs",
    "./dist/public/*.html",
    "./Server/src/**/*.{html,js,ejs,ts}",
  ],
  theme: {
    extend: {},
  },
  plugins: [],
};