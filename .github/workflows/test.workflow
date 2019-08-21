workflow "Build Solution" {
  on = "push"
  resolves = ["Generate"]
}

action "Generate" {
  uses = "actions/checkout@v1"
  args = "cmake . -Ax64 -B.build"
  runs = "windows-latest"
}
