# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "ubuntu/trusty64"
  config.ssh.forward_agent = true
  config.vm.synced_folder "/Users/gadomski/Projects", "/projects"
  config.vm.synced_folder "/Users/gadomski/src", "/src"
end
