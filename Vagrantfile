# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "ubuntu/precise32"
  config.ssh.forward_agent = true
  config.vm.synced_folder "/Users/gadomski/Projects", "/projects"
end
